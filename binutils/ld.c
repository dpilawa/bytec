/* 
 * 
 *    ld.c - this file is part of BYTEC/16 binutils (Linker)
 *   
 *    Copyright 2013 Dawid Pilawa
 * 
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "a.out.h"
#include "bytec.h"

extern void error(const char *, ...);
extern void print_verbose(const char *, ...);  

/* DEFINES */

#define undf(X) (((X->n_sclass&N_CLASS)==C_EXT) && ((X->n_sclass&N_SECT)==N_UNDF))
#define OP_JMP  (char)0x20
enum {RLC_TEXT, RLC_DATA};
enum {F_AOUT, F_IHEX};

/* GLOBALS */

const char usage[] = 
"Usage: ld-b16 [options] file...\n"
"Options:\n"
"  -o filename  Set output filename (default is a.out)\n"
"  -f format    Set output format (AOUT and IHEX, default is AOUT)\n"
"  -t address   Set relocation address of .text section (address must be hexadecimal)\n"
"  -d address   Set relocation address of .data section (address must be hexadecimal)\n"
"  -e address   Set entry address of data segment in Intel HEX file (only relevant with -f IHEX)\n"
"  -v           Set verbose output\n"
;

/* list of linked objects */
typedef struct flist 
{
    char*  filename;
    struct exec header;
    struct reloc *trelocs;
    struct reloc *drelocs;
    struct nlist2 *symbols;
    long n_trelocs;
    long n_drelocs;
    long n_symbols;
    char*  strx;  /* table of strings */ 
    struct flist *next;
} flist_t;

flist_t *files = NULL;

/* output object */
typedef struct out
{
    char* filename;
    struct exec header;
    char* text;
    char* data;    
    int format;
    long ihex_dentry;
} out_t;

out_t output;

/* auxiliary symbol list */ 
typedef struct symlist 
{
  char* s_name;               
  struct nlist2 *s; /* pointer to a.out symbol */
  flist_t* f; /* pointer to file data */ 
  unsigned short r_symndx; /* symbol index within its file (for relocs) */
  struct symlist *s_next;
} symlist_t;

symlist_t* symbols = NULL;

/* other globals */
extern int verbose;     /* verbose flag */

/* FUNCTIONS */

/* get symbol by name from auxiliary symbol list */
/* return: pointer to list element or null */
symlist_t* sym_get(const char *name)
{
    symlist_t* sl = symbols;
    
    while (sl)
    {
        if (strcmp(sl->s_name, name)==0)
            return sl;
        sl=sl->s_next;
    }
    
    return sl;
}

/* get real symbol value (i.e. value taking into account its object's offset in target object */
/* return: symbol value */
long sym_get_realval(symlist_t *symbol)
{
    return symbol->s->n_value + (((symbol->s->n_sclass)&N_SECT)==N_TEXT?(symbol->f->header.a_tbase):(symbol->f->header.a_dbase));
}

/* get defined symbol for a relocation based on reloc's symndx number */
/* raise error if symbol undefined */
/* return: pointer to list element or null */
symlist_t* sym_get_reloc(flist_t *file, struct reloc *r, const char *label)
{
    symlist_t* symbol;

    symbol = sym_get((file->strx + ((file->symbols + r->r_symndx - 1)->n_strx)));
    if (!symbol) 
    {
        error("Symbol %d not found in sym_get_reloc()\n", r->r_symndx);
    }
    if (undf(symbol->s))
    {
        error("Undefined reference to %s at %s:%s:0x%04x\n", symbol->s_name, file->filename, label, r->r_vaddr);
    }
    
    return symbol;
}

/* insert symbol to auxiliary symbol list */
/* return: none */
void sym_insert(struct nlist2 *s, flist_t *f, const char *name, unsigned short idx)
{
    symlist_t* sl = malloc(sizeof(symlist_t));
    
    sl->s_next = symbols;
    symbols = sl;
      
    sl->s = s;
    sl->f = f;
    sl->s_name = strdup(name);
    sl->r_symndx = idx;
}

/* initialize output data */
void setup_output()
{
    output.filename = NULL;
    output.format = F_AOUT;
    output.ihex_dentry = 0x10000;
    output.header.a_magic[0] = A_MAGIC0;
    output.header.a_magic[1] = A_MAGIC1;
    output.header.a_flags = (char)0;
    output.header.a_cpu = A_BYTEC16;
    output.header.a_hdrlen = (unsigned char)sizeof(struct exec);
    output.header.a_bss = (long)0;
    output.header.a_entry = (long)0;
    output.header.a_total = (long)0;
    output.header.a_syms = (long)0;    
    output.header.a_trsize = (long)0;
    output.header.a_drsize = (long)0; 
    output.header.a_text = (long)0;
    output.header.a_data = (long)0;   
    output.header.a_tbase = (long)0;
    output.header.a_dbase = (long)0;         
}

/* free all data structures, release memory */
void cleanup()
{
    symlist_t *s, *s0;
    flist_t *f, *f0;
    
    /* clean-up symbols */
    s = symbols;
    while (s)
    {
        s0 = s;
        s = s->s_next;
        free(s0->s_name);
        free(s0);
    }
    
    /* clean-up files */
    f = files;
    while (f)
    {
        f0 = f;
        f = f->next;
        
        free(f0->filename);
        free(f0->trelocs);
        free(f0->drelocs);
        free(f0->symbols);
        free(f0->strx);
        free(f0);
    }

    /* clean-up output */
    free(output.filename);
    free(output.text);
    free(output.data);
}

/* build auxiliary table of resolved symbols */
/* return: none */
void resolve_symbols()
{
    flist_t* file = files;
    struct nlist2 *s;
    symlist_t* s2;
    int i;

    /* iterate all files */
    while (file)
    {
        /* iterate all symbols in file */
        print_verbose(" File %s\n", file->filename);
        for (i=0; i<file->n_symbols; i++)
        {
            s = file->symbols + i;
            print_verbose("  Encountered symbol: %s ", file->strx + s->n_strx);
            s2 = sym_get(file->strx + s->n_strx);
            /* symbol exists and is undefined, or symbol does not exist */
            if ((s2 && undf(s2->s)) || !s2)
            {
                /* encountered another undefined occurrence undefined symbol - do nothing or add if symbol does not exist*/
                if (undf(s))
                {
                    print_verbose("extern undefined\n");
                    if (!s2)
                    {
                        sym_insert(s, file, file->strx + s->n_strx, i+1);
                    }
                }
                /* encountered a defined occurrence of undefined symbol - define or add */
                else
                {
                    /* resolve symbol if it existed, or add a new one otherwise */
                    print_verbose("defined ");
                    if (s2) 
                    {
                        s2->s = s;
                        s2->f = file;
                    }
                    else
                    {
                        sym_insert(s, file, file->strx + s->n_strx, i+1);
                    }
                    switch(s->n_sclass&N_SECT)
                    {
                        case N_TEXT:
                            print_verbose("text+");
                            break;
                        case N_DATA:
                            print_verbose("data+");
                            break;
                        default:
                            error("Undefined segment for symbol '%s' (%d)\n", file->strx + s->n_strx, s->n_sclass&N_SECT);
                            break;
                    }
                    print_verbose("0x%04x\n", s->n_value);
                }
            }
            /* symbol exists and is defined */
            else
            {
                /* encountered an undefined occurrence of previously defined symbol - do nothing or raise error in case of redefinition */
                if (undf(s))
                {
                    print_verbose("resolved %s:", s2->f->filename);
                    switch(s2->s->n_sclass&N_SECT)
                    {
                        case N_TEXT:
                            print_verbose("text+");
                            break;
                        case N_DATA:
                            print_verbose("data+");
                            break;
                        default:
                            error("Undefined segment for symbol '%s' (%d)\n", s2->f->strx + s2->s->n_strx, s2->s->n_sclass&N_SECT);
                            break;
                    }
                    print_verbose("0x%04x\n", s2->s->n_value);
                }
                /* encountered a defined occurrence of defined symbol - error */
                else
                {
                    print_verbose("redefined\n");
                    error("Redefinition of symbol '%s'\nPreviously defined here '%s+0x%04x'\n", file->strx + s->n_strx, s2->f->filename, s2->s->n_value);
                    exit(-1);
                }                    
            }
        }
        file=file->next;
    }
}

/* apply a given relocation in a given file */
/* return: none */
void reloc(struct reloc* r, flist_t* file, int r_seg)
{
    unsigned short r_val;   /* target value to be put at relocation address */
    long r_raddr;           /* relocation address within output buffer */
    long r_rbase;           /* relocation base */
    char *label;
    unsigned char *output_seg ;
    symlist_t *symbol;
    
    /* determine real relocation address and segment */
    if (r_seg==RLC_TEXT)
    {
        r_raddr = file->header.a_tbase+r->r_vaddr;
        r_rbase = output.header.a_tbase;
        label = strdup("text");
        output_seg = output.text;
    }
    else if (r_seg==RLC_DATA)
    {
        r_raddr = file->header.a_dbase+r->r_vaddr;
        r_rbase = output.header.a_dbase;
        label = strdup("data"); 
        output_seg = output.data;
    }
    else 
    {
        error("Invalid relocation segment in reloc()\n");
    }
    print_verbose("  Reloc of %s:%s+0x%04x [output:%s+0x%04x]", file->filename, label, r->r_vaddr, label, r_raddr);
    
    /* calculate relocation value (new value to be put at relocation address) */
    switch (r->r_type)
    {
        /* absolute relocations */
        case R_ABBS:
            switch(r->r_symndx)
            {
                /* absolute local relocation - add object's text segment base to the reference */
                case S_TEXT:
                    r_val = ((*(output_seg+r_raddr-r_rbase))<<8) + *(output_seg+r_raddr-r_rbase+1) + file->header.a_tbase;
                    print_verbose(" to 0x%04x (absolute local reference changed by relocation of text segment)\n", r_val);
                    break;
                /* absolute local relocation - add object's data segment base to the reference */
                case S_DATA:
                    r_val = ((*(output_seg+r_raddr-r_rbase))<<8) + *(output_seg+r_raddr-r_rbase+1) + file->header.a_dbase;
                    print_verbose(" to 0x%04x (absolute local reference changed by relocation of data segment)\n", r_val);
                    break;
                /* currently unused - raise error */
                case S_ABS:
                case S_BSS:
                    error("Invalid relocation segment for absolute relocation in %s:text+0x%04x\n", file->filename, r->r_vaddr);
                    break;
                /* absolute extern relocation - put resolved value of the symbol at relocation address or raise error if symbol is undefined */
                default:
                    symbol = sym_get_reloc(file, r, label);
                    r_val = sym_get_realval(symbol);
                    print_verbose(" to 0x%04x (absolute extern reference to symbol %s)\n", r_val, symbol->s_name);
                    break;
            }
            break;
        /* PC-relative relocations */
        case R_PCRBYTE:
            /* pc-relative extern relocation - put relative vector to the resolved value of the symbol at relocation address or raise error if symbol is undefined */
            symbol = sym_get_reloc(file, r, label);
            r_val = sym_get_realval(symbol) - (r_raddr + 2); /* 2 byte offset is to move hyphotetical PC after the PC-relative instruction */
            print_verbose(" to 0x%04x (pc-relative extern reference to symbol %s)\n", r_val, symbol->s_name);
            break;
        /* error - unknown relocation type */
        default:
            error("Invalid relocation type at %s:text+0x%04x\n", file->filename, r->r_vaddr);
            break;
    }
    
    free(label);
    
    /* write calculated relocation value at relocation address in output object */
    *(output_seg+r_raddr-r_rbase)=(char)((r_val&0xff00)>>8);
    *(output_seg+r_raddr-r_rbase+1)=(char)(r_val&0x00ff);
}

/* apply all relocations to linked object */
/* return: none */
void apply_relocs()
{
    flist_t* file = files;
    long i;
    struct reloc* r;
    
    /* iterate all files */
    while (file)
    {
        /* iterate all relocations in a file */
        print_verbose(" File %s [tbase 0x%04x, dbase 0x%04x]\n", file->filename, file->header.a_tbase, file->header.a_dbase);
        
        /* do text segment relocations */
        for (i=0; i<file->n_trelocs; i++)
        {
            r = (file->trelocs + i);
            reloc(r, file, RLC_TEXT);
        }
        
        /* do data segment relocations */
        for (i=0; i<file->n_drelocs; i++)
        {
            r = (file->drelocs + i);
            reloc(r, file, RLC_DATA);
        }
        
        file=file->next;
    }
}

/* perform actual object linking */
void do_link()
{
    /* resolve symbols in all objects */
    print_verbose("Resolving symbols:\n");
    resolve_symbols();
    /* apply relocations */
    print_verbose("Applying relocations:\n");
    apply_relocs();
}

/* write an Intel HEX file segment */
void write_ihex_seg(FILE* f, unsigned char* buf, unsigned long len, unsigned long seg_entry)
{
    unsigned short checksum;
    unsigned short i, j;
    unsigned short reclen;  
    
    if (len > 0) 
    {
        fprintf(f, ":02000002%04X", (unsigned short)(seg_entry >> 4));
        checksum = 0x02 + 0x02 + ((unsigned short)(seg_entry >> 4) & 0x00ff) + (((unsigned short)(seg_entry >> 4) >> 8) & 0x00ff);
        checksum = (0x0100 - (checksum & 0x00ff)) & 0x00ff;
        fprintf(f, "%02X\n", checksum);
        for (i = 0; i < len; i = i + 16)
        {
            reclen = (len - i) >= 16 ? 16 : len - i;
            checksum = reclen + (i & 0x00ff) + (i >> 8);
            fprintf(f, ":%02X%04X00", reclen, i);
            for (j = i; j < i + reclen; j++)
            {
                fprintf(f, "%02X", *(buf + j));
                checksum = checksum + *(buf + j);
            }
            checksum = (0x0100 - (checksum & 0x00ff)) & 0x00ff;
            fprintf(f, "%02X\n", checksum); 
        }
    }   
}

/* write output Intel HEX file */
void write_ihex(const char* filename)
{
    FILE* f;
    
    if (f = fopen(filename, "w"))
    {
        /* text segment */
        write_ihex_seg(f, output.text, output.header.a_text, output.header.a_tbase);

        /* data segment */
        write_ihex_seg(f, output.data, output.header.a_data, output.ihex_dentry + output.header.a_dbase);
        
        /* EOF */
        fprintf(f, ":00000001FF\n");
        fclose(f);
    }
    else
    {
        error( "Unable to open file '%s' for writing\n", filename);
        exit(-1);
    }
}

/* write output a.out file */
void write_aout(const char* filename)
{
    FILE* f;
    if (f = fopen(filename, "wb"))
    {
        fwrite(&output.header, sizeof(struct exec), 1, f);
        fwrite(output.text, output.header.a_text, 1, f);
        fwrite(output.data, output.header.a_data, 1, f);
        fclose(f);
    }
    else
    {
        error( "Unable to open file '%s' for writing\n", filename);
        exit(-1);
    }
}

/* read input a.out file */
void read_aout(const char* filename)
{
    FILE* f;
    long strx_size;
    
    if (f = fopen(filename, "rb"))
    {
    
        flist_t *file = malloc(sizeof(flist_t));
        file->next = files;
        file->filename = strdup(filename);
        files = file;
                
        /* read header */
        fread(&file->header, sizeof(struct exec), 1, f);
        if (BADMAG(file->header)) 
        {
            error("Invalid a.out file '%s' (bad magic number)\n", file->filename);
        }

        /* set entry addresses */
        file->header.a_tbase = output.header.a_tbase + output.header.a_text;
        file->header.a_dbase = output.header.a_dbase + output.header.a_data;
        
        /* allocate memory and read segments */
        output.text = realloc(output.text, output.header.a_text+file->header.a_text);
        output.data = realloc(output.data, output.header.a_data+file->header.a_data);
        fread(output.text+output.header.a_text, file->header.a_text, 1, f);
        fread(output.data+output.header.a_data, file->header.a_data, 1, f);
        output.header.a_text += file->header.a_text;
        output.header.a_data += file->header.a_data;    
        
        /* alocate memory and read relocations */
        file->trelocs = malloc(file->header.a_trsize);
        file->drelocs = malloc(file->header.a_drsize);
        fread(file->trelocs, sizeof(struct reloc), file->header.a_trsize / sizeof(struct reloc), f);
        fread(file->drelocs, sizeof(struct reloc), file->header.a_drsize / sizeof(struct reloc), f);
        file->n_trelocs = file->header.a_trsize / sizeof(struct reloc);
        file->n_drelocs = file->header.a_drsize / sizeof(struct reloc);

        /* alocate memory and read symbols and symbol string table */
        file->symbols = malloc(file->header.a_syms);
        fread(file->symbols, sizeof(struct nlist2), file->header.a_syms / sizeof(struct nlist2), f);
        fread(&strx_size, sizeof(strx_size), 1, f);
        file->n_symbols = file->header.a_syms / sizeof(struct nlist2);
        file->strx = malloc(strx_size);
        fread(file->strx, strx_size, 1, f);
        
        fclose(f);
    
    }
    else
    {
        error( "Unable to open file '%s' for reading\n", filename);
        exit(-1);
    }
}

/* main function, top-level routine */
int main(int argc, char **argv)
{

    char c;
    int i;
    char** files = NULL;
    int file_cnt = 0;
    
    setup_output();
    
    /* parse command line parameters */
    while ((c = getopt (argc, argv, "-vo:d:t:f:e:")) != -1)
        switch (c) 
        {
            case 1:
                file_cnt++;
                files = (char**)realloc(files, sizeof(char*) * file_cnt);
                files[file_cnt-1] = strdup(optarg);
                break;
            case 'v':
                verbose = 1;
                break;
            case 'o':
                output.filename = strdup(optarg);
                break;
            case 'd':
                output.header.a_dbase = strtoul(optarg, NULL, 16);
                break;
            case 't':
                output.header.a_tbase = strtoul(optarg, NULL, 16);
                break;     
            case 'e':
                output.ihex_dentry = strtoul(optarg, NULL, 16);
                break;
            case 'f':
                if (strcmp(optarg, "AOUT")==0) 
                {
                    output.format = F_AOUT;
                }    
                else if (strcmp(optarg, "IHEX")==0) 
                {
                    output.format = F_IHEX;
                }
                else 
                {
                    error("%s is not a valid output format (use AOUT or IHEX)\n%s", optarg, usage);
                }
                break;
            case '?':
                error("%s", usage);
                exit(-1);
                break;
            default:
                abort();
           }
    
    if (!output.filename)
    {
        output.filename = strdup("a.out");
    }

    if (!file_cnt) 
    {
        error("Missing input filename(s)\n%s", usage);      
    }
    else
    {
        print_verbose("Processing input files:\n");
        for (i=0; i<file_cnt; i++) 
        {
            print_verbose(" File %s\n", *(files+i));
            read_aout(*(files+i));
            free(*(files+i));
        }
        free(files);
    }
    
    do_link();
    
    print_verbose("Writing output file %s (%d bytes text, %d bytes data, tbase 0x%04x, thigh 0x%04x, dbase 0x%04x, dhigh 0x%04x)\n", output.filename, output.header.a_text, \
                  output.header.a_data, output.header.a_tbase, output.header.a_tbase + output.header.a_text - 1, output.header.a_dbase, output.header.a_dbase + output.header.a_data - 1);
    switch (output.format)
    {
        case F_AOUT:
            write_aout(output.filename);
            break;
        case F_IHEX:
            write_ihex(output.filename);
            break;
        default:
            error("Unknown output file format\n");
            break;
    }
    cleanup();
  
    return 0;
}
