<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N" xrefpart="/%S.%C%R">
<libraries>
<library name="supply2">
<packages>
</packages>
<symbols>
<symbol name="+05V">
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.1524" layer="94"/>
<wire x1="0" y1="0.635" x2="0" y2="1.905" width="0.1524" layer="94"/>
<circle x="0" y="1.27" radius="1.27" width="0.254" layer="94"/>
<text x="-1.905" y="3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="GND">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="-1.905" y="-3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="+5V" prefix="SUPPLY">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="+5V" symbol="+05V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="SUPPLY">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="GND" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="frames">
<packages>
</packages>
<symbols>
<symbol name="DINA3_L">
<frame x1="0" y1="0" x2="388.62" y2="264.16" columns="4" rows="4" layer="94" border-left="no" border-top="no" border-right="no" border-bottom="no"/>
</symbol>
<symbol name="DOCFIELD">
<wire x1="0" y1="0" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="87.63" y2="15.24" width="0.1016" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="71.12" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="0" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="87.63" y1="5.08" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="0" y1="15.24" x2="0" y2="22.86" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="22.86" x2="101.6" y2="15.24" width="0.1016" layer="94"/>
<text x="1.27" y="1.27" size="2.54" layer="94" font="vector">Date:</text>
<text x="12.7" y="1.27" size="2.54" layer="94" font="vector">&gt;LAST_DATE_TIME</text>
<text x="72.39" y="1.27" size="2.54" layer="94" font="vector">Sheet:</text>
<text x="86.36" y="1.27" size="2.54" layer="94" font="vector">&gt;SHEET</text>
<text x="88.9" y="11.43" size="2.54" layer="94" font="vector">REV:</text>
<text x="1.27" y="19.05" size="2.54" layer="94" font="vector">TITLE:</text>
<text x="1.27" y="11.43" size="2.54" layer="94" font="vector">Document Number:</text>
<text x="17.78" y="19.05" size="2.54" layer="94" font="vector">&gt;DRAWING_NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="DINA3_L" prefix="FRAME" uservalue="yes">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A3, landscape with extra doc field</description>
<gates>
<gate name="G$1" symbol="DINA3_L" x="0" y="0"/>
<gate name="G$2" symbol="DOCFIELD" x="287.02" y="0" addlevel="must"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pinhead">
<description>&lt;b&gt;Pin Header Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="2X02">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-2.54" y1="-1.905" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-2.54" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="1.27" y="1.27" drill="1.016" shape="octagon"/>
<text x="-2.54" y="3.175" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-4.445" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
</package>
<package name="2X02/90">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<pad name="2" x="-1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="4" x="1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="1" x="-1.27" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="3" x="1.27" y="-6.35" drill="1.016" shape="octagon"/>
<text x="-3.175" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.445" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-5.461" x2="-0.889" y2="-4.699" layer="21"/>
<rectangle x1="-1.651" y1="-4.699" x2="-0.889" y2="-2.921" layer="51"/>
<rectangle x1="0.889" y1="-4.699" x2="1.651" y2="-2.921" layer="51"/>
<rectangle x1="0.889" y1="-5.461" x2="1.651" y2="-4.699" layer="21"/>
</package>
<package name="2X08">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-10.16" y1="-1.905" x2="-9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-2.54" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.54" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-2.54" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.905" x2="-9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="2.54" x2="-7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="2.54" x2="-5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="2.54" x2="5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="2.54" x2="6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="6.985" y1="2.54" x2="7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-2.54" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-2.54" x2="4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-2.54" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-2.54" x2="-3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-2.54" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-2.54" x2="-8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="8.255" y1="2.54" x2="9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="2.54" x2="10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="8.255" y1="-2.54" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<pad name="1" x="-8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="-3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="-3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="-1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="-1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="15" x="8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="16" x="8.89" y="1.27" drill="1.016" shape="octagon"/>
<text x="-10.16" y="3.175" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-10.16" y="-4.445" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-9.144" y1="-1.524" x2="-8.636" y2="-1.016" layer="51"/>
<rectangle x1="-9.144" y1="1.016" x2="-8.636" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="1.016" x2="-6.096" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="-1.524" x2="-6.096" y2="-1.016" layer="51"/>
<rectangle x1="-4.064" y1="1.016" x2="-3.556" y2="1.524" layer="51"/>
<rectangle x1="-4.064" y1="-1.524" x2="-3.556" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="3.556" y1="1.016" x2="4.064" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="3.556" y1="-1.524" x2="4.064" y2="-1.016" layer="51"/>
<rectangle x1="6.096" y1="1.016" x2="6.604" y2="1.524" layer="51"/>
<rectangle x1="6.096" y1="-1.524" x2="6.604" y2="-1.016" layer="51"/>
<rectangle x1="8.636" y1="1.016" x2="9.144" y2="1.524" layer="51"/>
<rectangle x1="8.636" y1="-1.524" x2="9.144" y2="-1.016" layer="51"/>
</package>
<package name="2X08/90">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-10.16" y1="-1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="6.985" x2="-8.89" y2="1.27" width="0.762" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="6.985" x2="-6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="6.985" x2="-3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="6.985" x2="3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0.635" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="6.985" x2="6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="8.89" y1="6.985" x2="8.89" y2="1.27" width="0.762" layer="21"/>
<pad name="2" x="-8.89" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="4" x="-6.35" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="6" x="-3.81" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="8" x="-1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="10" x="1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="12" x="3.81" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="14" x="6.35" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="16" x="8.89" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="1" x="-8.89" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="3" x="-6.35" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="5" x="-3.81" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="7" x="-1.27" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="9" x="1.27" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="11" x="3.81" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="13" x="6.35" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="15" x="8.89" y="-6.35" drill="1.016" shape="octagon"/>
<text x="-10.795" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="12.065" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-9.271" y1="0.635" x2="-8.509" y2="1.143" layer="21"/>
<rectangle x1="-6.731" y1="0.635" x2="-5.969" y2="1.143" layer="21"/>
<rectangle x1="-4.191" y1="0.635" x2="-3.429" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="3.429" y1="0.635" x2="4.191" y2="1.143" layer="21"/>
<rectangle x1="5.969" y1="0.635" x2="6.731" y2="1.143" layer="21"/>
<rectangle x1="8.509" y1="0.635" x2="9.271" y2="1.143" layer="21"/>
<rectangle x1="-9.271" y1="-2.921" x2="-8.509" y2="-1.905" layer="21"/>
<rectangle x1="-6.731" y1="-2.921" x2="-5.969" y2="-1.905" layer="21"/>
<rectangle x1="-9.271" y1="-5.461" x2="-8.509" y2="-4.699" layer="21"/>
<rectangle x1="-9.271" y1="-4.699" x2="-8.509" y2="-2.921" layer="51"/>
<rectangle x1="-6.731" y1="-4.699" x2="-5.969" y2="-2.921" layer="51"/>
<rectangle x1="-6.731" y1="-5.461" x2="-5.969" y2="-4.699" layer="21"/>
<rectangle x1="-4.191" y1="-2.921" x2="-3.429" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="-4.191" y1="-5.461" x2="-3.429" y2="-4.699" layer="21"/>
<rectangle x1="-4.191" y1="-4.699" x2="-3.429" y2="-2.921" layer="51"/>
<rectangle x1="-1.651" y1="-4.699" x2="-0.889" y2="-2.921" layer="51"/>
<rectangle x1="-1.651" y1="-5.461" x2="-0.889" y2="-4.699" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="3.429" y1="-2.921" x2="4.191" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-5.461" x2="1.651" y2="-4.699" layer="21"/>
<rectangle x1="0.889" y1="-4.699" x2="1.651" y2="-2.921" layer="51"/>
<rectangle x1="3.429" y1="-4.699" x2="4.191" y2="-2.921" layer="51"/>
<rectangle x1="3.429" y1="-5.461" x2="4.191" y2="-4.699" layer="21"/>
<rectangle x1="5.969" y1="-2.921" x2="6.731" y2="-1.905" layer="21"/>
<rectangle x1="8.509" y1="-2.921" x2="9.271" y2="-1.905" layer="21"/>
<rectangle x1="5.969" y1="-5.461" x2="6.731" y2="-4.699" layer="21"/>
<rectangle x1="5.969" y1="-4.699" x2="6.731" y2="-2.921" layer="51"/>
<rectangle x1="8.509" y1="-4.699" x2="9.271" y2="-2.921" layer="51"/>
<rectangle x1="8.509" y1="-5.461" x2="9.271" y2="-4.699" layer="21"/>
</package>
<package name="2X18">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-22.86" y1="-1.905" x2="-22.225" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-22.225" y1="-2.54" x2="-20.955" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-20.955" y1="-2.54" x2="-20.32" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-20.32" y1="-1.905" x2="-19.685" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="-2.54" x2="-18.415" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-18.415" y1="-2.54" x2="-17.78" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="-1.905" x2="-17.145" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="-2.54" x2="-15.875" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="-2.54" x2="-15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="-1.905" x2="-14.605" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="-2.54" x2="-13.335" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="-2.54" x2="-12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-1.905" x2="-12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="-2.54" x2="-10.795" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="-2.54" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="-2.54" x2="-8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-2.54" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-22.86" y1="-1.905" x2="-22.86" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-22.86" y1="1.905" x2="-22.225" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-22.225" y1="2.54" x2="-20.955" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-20.955" y1="2.54" x2="-20.32" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-20.32" y1="1.905" x2="-19.685" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-19.685" y1="2.54" x2="-18.415" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-18.415" y1="2.54" x2="-17.78" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="1.905" x2="-17.145" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-17.145" y1="2.54" x2="-15.875" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-15.875" y1="2.54" x2="-15.24" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="1.905" x2="-14.605" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-14.605" y1="2.54" x2="-13.335" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-13.335" y1="2.54" x2="-12.7" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="1.905" x2="-12.065" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-12.065" y1="2.54" x2="-10.795" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-10.795" y1="2.54" x2="-10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.905" x2="-9.525" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="2.54" x2="-8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="2.54" x2="-7.62" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="2.54" x2="-5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0" y2="1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="2.54" x2="5.08" y2="1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="2.54" x2="6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="6.985" y2="2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="2.54" x2="8.255" y2="2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="2.54" x2="10.16" y2="1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="1.905" x2="10.795" y2="2.54" width="0.1524" layer="21"/>
<wire x1="12.065" y1="2.54" x2="10.795" y2="2.54" width="0.1524" layer="21"/>
<wire x1="12.065" y1="2.54" x2="12.7" y2="1.905" width="0.1524" layer="21"/>
<wire x1="12.7" y1="1.905" x2="13.335" y2="2.54" width="0.1524" layer="21"/>
<wire x1="14.605" y1="2.54" x2="13.335" y2="2.54" width="0.1524" layer="21"/>
<wire x1="14.605" y1="2.54" x2="15.24" y2="1.905" width="0.1524" layer="21"/>
<wire x1="15.24" y1="1.905" x2="15.875" y2="2.54" width="0.1524" layer="21"/>
<wire x1="17.145" y1="2.54" x2="15.875" y2="2.54" width="0.1524" layer="21"/>
<wire x1="17.145" y1="2.54" x2="17.78" y2="1.905" width="0.1524" layer="21"/>
<wire x1="17.78" y1="1.905" x2="18.415" y2="2.54" width="0.1524" layer="21"/>
<wire x1="19.685" y1="2.54" x2="18.415" y2="2.54" width="0.1524" layer="21"/>
<wire x1="19.685" y1="2.54" x2="20.32" y2="1.905" width="0.1524" layer="21"/>
<wire x1="20.32" y1="1.905" x2="20.955" y2="2.54" width="0.1524" layer="21"/>
<wire x1="22.225" y1="2.54" x2="20.955" y2="2.54" width="0.1524" layer="21"/>
<wire x1="22.225" y1="2.54" x2="22.86" y2="1.905" width="0.1524" layer="21"/>
<wire x1="22.86" y1="-1.905" x2="22.225" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="22.225" y1="-2.54" x2="20.955" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="20.32" y1="-1.905" x2="20.955" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="20.32" y1="-1.905" x2="19.685" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="19.685" y1="-2.54" x2="18.415" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="17.78" y1="-1.905" x2="18.415" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="17.78" y1="-1.905" x2="17.145" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="15.875" y1="-2.54" x2="17.145" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="15.875" y1="-2.54" x2="15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="15.24" y1="-1.905" x2="14.605" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="13.335" y1="-2.54" x2="14.605" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="13.335" y1="-2.54" x2="12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="12.7" y1="-1.905" x2="12.065" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="12.065" y1="-2.54" x2="10.795" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="10.795" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="9.525" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-2.54" x2="8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="8.255" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="6.985" y1="-2.54" x2="5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-2.54" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.54" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-6.985" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-20.32" y1="1.905" x2="-20.32" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="1.905" x2="-17.78" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="1.905" x2="-15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="1.905" x2="-12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.905" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="12.7" y1="1.905" x2="12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="15.24" y1="1.905" x2="15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="17.78" y1="1.905" x2="17.78" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="20.32" y1="1.905" x2="20.32" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="22.86" y1="1.905" x2="22.86" y2="-1.905" width="0.1524" layer="21"/>
<pad name="1" x="-21.59" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-21.59" y="1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-19.05" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-19.05" y="1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="-16.51" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="-16.51" y="1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="-13.97" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="-13.97" y="1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="-11.43" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="-11.43" y="1.27" drill="1.016" shape="octagon"/>
<pad name="11" x="-8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="12" x="-8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="13" x="-6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="14" x="-6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="15" x="-3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="16" x="-3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="17" x="-1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="18" x="-1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="19" x="1.27" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="20" x="1.27" y="1.27" drill="1.016" shape="octagon"/>
<pad name="21" x="3.81" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="22" x="3.81" y="1.27" drill="1.016" shape="octagon"/>
<pad name="23" x="6.35" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="24" x="6.35" y="1.27" drill="1.016" shape="octagon"/>
<pad name="25" x="8.89" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="26" x="8.89" y="1.27" drill="1.016" shape="octagon"/>
<pad name="27" x="11.43" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="28" x="11.43" y="1.27" drill="1.016" shape="octagon"/>
<pad name="29" x="13.97" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="30" x="13.97" y="1.27" drill="1.016" shape="octagon"/>
<pad name="31" x="16.51" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="32" x="16.51" y="1.27" drill="1.016" shape="octagon"/>
<pad name="33" x="19.05" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="34" x="19.05" y="1.27" drill="1.016" shape="octagon"/>
<pad name="35" x="21.59" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="36" x="21.59" y="1.27" drill="1.016" shape="octagon"/>
<text x="-22.86" y="3.175" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-22.86" y="-4.445" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-21.844" y1="-1.524" x2="-21.336" y2="-1.016" layer="51"/>
<rectangle x1="-21.844" y1="1.016" x2="-21.336" y2="1.524" layer="51"/>
<rectangle x1="-19.304" y1="1.016" x2="-18.796" y2="1.524" layer="51"/>
<rectangle x1="-19.304" y1="-1.524" x2="-18.796" y2="-1.016" layer="51"/>
<rectangle x1="-16.764" y1="1.016" x2="-16.256" y2="1.524" layer="51"/>
<rectangle x1="-16.764" y1="-1.524" x2="-16.256" y2="-1.016" layer="51"/>
<rectangle x1="-14.224" y1="1.016" x2="-13.716" y2="1.524" layer="51"/>
<rectangle x1="-11.684" y1="1.016" x2="-11.176" y2="1.524" layer="51"/>
<rectangle x1="-9.144" y1="1.016" x2="-8.636" y2="1.524" layer="51"/>
<rectangle x1="-14.224" y1="-1.524" x2="-13.716" y2="-1.016" layer="51"/>
<rectangle x1="-11.684" y1="-1.524" x2="-11.176" y2="-1.016" layer="51"/>
<rectangle x1="-9.144" y1="-1.524" x2="-8.636" y2="-1.016" layer="51"/>
<rectangle x1="-6.604" y1="1.016" x2="-6.096" y2="1.524" layer="51"/>
<rectangle x1="-6.604" y1="-1.524" x2="-6.096" y2="-1.016" layer="51"/>
<rectangle x1="-4.064" y1="1.016" x2="-3.556" y2="1.524" layer="51"/>
<rectangle x1="-4.064" y1="-1.524" x2="-3.556" y2="-1.016" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="3.556" y1="1.016" x2="4.064" y2="1.524" layer="51"/>
<rectangle x1="3.556" y1="-1.524" x2="4.064" y2="-1.016" layer="51"/>
<rectangle x1="6.096" y1="1.016" x2="6.604" y2="1.524" layer="51"/>
<rectangle x1="6.096" y1="-1.524" x2="6.604" y2="-1.016" layer="51"/>
<rectangle x1="8.636" y1="1.016" x2="9.144" y2="1.524" layer="51"/>
<rectangle x1="8.636" y1="-1.524" x2="9.144" y2="-1.016" layer="51"/>
<rectangle x1="11.176" y1="1.016" x2="11.684" y2="1.524" layer="51"/>
<rectangle x1="11.176" y1="-1.524" x2="11.684" y2="-1.016" layer="51"/>
<rectangle x1="13.716" y1="1.016" x2="14.224" y2="1.524" layer="51"/>
<rectangle x1="13.716" y1="-1.524" x2="14.224" y2="-1.016" layer="51"/>
<rectangle x1="16.256" y1="1.016" x2="16.764" y2="1.524" layer="51"/>
<rectangle x1="16.256" y1="-1.524" x2="16.764" y2="-1.016" layer="51"/>
<rectangle x1="18.796" y1="1.016" x2="19.304" y2="1.524" layer="51"/>
<rectangle x1="18.796" y1="-1.524" x2="19.304" y2="-1.016" layer="51"/>
<rectangle x1="21.336" y1="1.016" x2="21.844" y2="1.524" layer="51"/>
<rectangle x1="21.336" y1="-1.524" x2="21.844" y2="-1.016" layer="51"/>
</package>
<package name="2X18/90">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-22.86" y1="-1.905" x2="-20.32" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-20.32" y1="-1.905" x2="-20.32" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-20.32" y1="0.635" x2="-22.86" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-22.86" y1="0.635" x2="-22.86" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-21.59" y1="6.985" x2="-21.59" y2="1.27" width="0.762" layer="21"/>
<wire x1="-20.32" y1="-1.905" x2="-17.78" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="-1.905" x2="-17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="0.635" x2="-20.32" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-19.05" y1="6.985" x2="-19.05" y2="1.27" width="0.762" layer="21"/>
<wire x1="-17.78" y1="-1.905" x2="-15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="-1.905" x2="-15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-15.24" y1="0.635" x2="-17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-16.51" y1="6.985" x2="-16.51" y2="1.27" width="0.762" layer="21"/>
<wire x1="-15.24" y1="-1.905" x2="-12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-1.905" x2="-12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="0.635" x2="-15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-13.97" y1="6.985" x2="-13.97" y2="1.27" width="0.762" layer="21"/>
<wire x1="-12.7" y1="-1.905" x2="-10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-11.43" y1="6.985" x2="-11.43" y2="1.27" width="0.762" layer="21"/>
<wire x1="-10.16" y1="-1.905" x2="-7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="6.985" x2="-8.89" y2="1.27" width="0.762" layer="21"/>
<wire x1="-7.62" y1="-1.905" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="6.985" x2="-6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="-5.08" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="6.985" x2="-3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="6.985" x2="3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="7.62" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0.635" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="6.985" x2="6.35" y2="1.27" width="0.762" layer="21"/>
<wire x1="7.62" y1="-1.905" x2="10.16" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="8.89" y1="6.985" x2="8.89" y2="1.27" width="0.762" layer="21"/>
<wire x1="10.16" y1="-1.905" x2="12.7" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="12.7" y1="-1.905" x2="12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="12.7" y1="0.635" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="11.43" y1="6.985" x2="11.43" y2="1.27" width="0.762" layer="21"/>
<wire x1="12.7" y1="-1.905" x2="15.24" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="15.24" y1="-1.905" x2="15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="15.24" y1="0.635" x2="12.7" y2="0.635" width="0.1524" layer="21"/>
<wire x1="13.97" y1="6.985" x2="13.97" y2="1.27" width="0.762" layer="21"/>
<wire x1="15.24" y1="-1.905" x2="17.78" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="17.78" y1="-1.905" x2="17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="17.78" y1="0.635" x2="15.24" y2="0.635" width="0.1524" layer="21"/>
<wire x1="16.51" y1="6.985" x2="16.51" y2="1.27" width="0.762" layer="21"/>
<wire x1="17.78" y1="-1.905" x2="20.32" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="20.32" y1="-1.905" x2="20.32" y2="0.635" width="0.1524" layer="21"/>
<wire x1="20.32" y1="0.635" x2="17.78" y2="0.635" width="0.1524" layer="21"/>
<wire x1="19.05" y1="6.985" x2="19.05" y2="1.27" width="0.762" layer="21"/>
<wire x1="20.32" y1="-1.905" x2="22.86" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="22.86" y1="-1.905" x2="22.86" y2="0.635" width="0.1524" layer="21"/>
<wire x1="22.86" y1="0.635" x2="20.32" y2="0.635" width="0.1524" layer="21"/>
<wire x1="21.59" y1="6.985" x2="21.59" y2="1.27" width="0.762" layer="21"/>
<pad name="2" x="-21.59" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="4" x="-19.05" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="6" x="-16.51" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="8" x="-13.97" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="10" x="-11.43" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="12" x="-8.89" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="14" x="-6.35" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="16" x="-3.81" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="18" x="-1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="20" x="1.27" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="22" x="3.81" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="24" x="6.35" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="26" x="8.89" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="28" x="11.43" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="30" x="13.97" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="32" x="16.51" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="34" x="19.05" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="36" x="21.59" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="1" x="-21.59" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="3" x="-19.05" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="5" x="-16.51" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="7" x="-13.97" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="9" x="-11.43" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="11" x="-8.89" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="13" x="-6.35" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="15" x="-3.81" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="17" x="-1.27" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="19" x="1.27" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="21" x="3.81" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="23" x="6.35" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="25" x="8.89" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="27" x="11.43" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="29" x="13.97" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="31" x="16.51" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="33" x="19.05" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="35" x="21.59" y="-6.35" drill="1.016" shape="octagon"/>
<text x="-23.495" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="24.765" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-21.971" y1="0.635" x2="-21.209" y2="1.143" layer="21"/>
<rectangle x1="-19.431" y1="0.635" x2="-18.669" y2="1.143" layer="21"/>
<rectangle x1="-16.891" y1="0.635" x2="-16.129" y2="1.143" layer="21"/>
<rectangle x1="-14.351" y1="0.635" x2="-13.589" y2="1.143" layer="21"/>
<rectangle x1="-11.811" y1="0.635" x2="-11.049" y2="1.143" layer="21"/>
<rectangle x1="-9.271" y1="0.635" x2="-8.509" y2="1.143" layer="21"/>
<rectangle x1="-6.731" y1="0.635" x2="-5.969" y2="1.143" layer="21"/>
<rectangle x1="-4.191" y1="0.635" x2="-3.429" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="3.429" y1="0.635" x2="4.191" y2="1.143" layer="21"/>
<rectangle x1="5.969" y1="0.635" x2="6.731" y2="1.143" layer="21"/>
<rectangle x1="8.509" y1="0.635" x2="9.271" y2="1.143" layer="21"/>
<rectangle x1="11.049" y1="0.635" x2="11.811" y2="1.143" layer="21"/>
<rectangle x1="13.589" y1="0.635" x2="14.351" y2="1.143" layer="21"/>
<rectangle x1="16.129" y1="0.635" x2="16.891" y2="1.143" layer="21"/>
<rectangle x1="18.669" y1="0.635" x2="19.431" y2="1.143" layer="21"/>
<rectangle x1="21.209" y1="0.635" x2="21.971" y2="1.143" layer="21"/>
<rectangle x1="-21.971" y1="-2.921" x2="-21.209" y2="-1.905" layer="21"/>
<rectangle x1="-19.431" y1="-2.921" x2="-18.669" y2="-1.905" layer="21"/>
<rectangle x1="-21.971" y1="-5.461" x2="-21.209" y2="-4.699" layer="21"/>
<rectangle x1="-21.971" y1="-4.699" x2="-21.209" y2="-2.921" layer="51"/>
<rectangle x1="-19.431" y1="-4.699" x2="-18.669" y2="-2.921" layer="51"/>
<rectangle x1="-19.431" y1="-5.461" x2="-18.669" y2="-4.699" layer="21"/>
<rectangle x1="-16.891" y1="-2.921" x2="-16.129" y2="-1.905" layer="21"/>
<rectangle x1="-14.351" y1="-2.921" x2="-13.589" y2="-1.905" layer="21"/>
<rectangle x1="-16.891" y1="-5.461" x2="-16.129" y2="-4.699" layer="21"/>
<rectangle x1="-16.891" y1="-4.699" x2="-16.129" y2="-2.921" layer="51"/>
<rectangle x1="-14.351" y1="-4.699" x2="-13.589" y2="-2.921" layer="51"/>
<rectangle x1="-14.351" y1="-5.461" x2="-13.589" y2="-4.699" layer="21"/>
<rectangle x1="-11.811" y1="-2.921" x2="-11.049" y2="-1.905" layer="21"/>
<rectangle x1="-11.811" y1="-5.461" x2="-11.049" y2="-4.699" layer="21"/>
<rectangle x1="-11.811" y1="-4.699" x2="-11.049" y2="-2.921" layer="51"/>
<rectangle x1="-9.271" y1="-2.921" x2="-8.509" y2="-1.905" layer="21"/>
<rectangle x1="-6.731" y1="-2.921" x2="-5.969" y2="-1.905" layer="21"/>
<rectangle x1="-9.271" y1="-5.461" x2="-8.509" y2="-4.699" layer="21"/>
<rectangle x1="-9.271" y1="-4.699" x2="-8.509" y2="-2.921" layer="51"/>
<rectangle x1="-6.731" y1="-4.699" x2="-5.969" y2="-2.921" layer="51"/>
<rectangle x1="-6.731" y1="-5.461" x2="-5.969" y2="-4.699" layer="21"/>
<rectangle x1="-4.191" y1="-2.921" x2="-3.429" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="-4.191" y1="-5.461" x2="-3.429" y2="-4.699" layer="21"/>
<rectangle x1="-4.191" y1="-4.699" x2="-3.429" y2="-2.921" layer="51"/>
<rectangle x1="-1.651" y1="-4.699" x2="-0.889" y2="-2.921" layer="51"/>
<rectangle x1="-1.651" y1="-5.461" x2="-0.889" y2="-4.699" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-5.461" x2="1.651" y2="-4.699" layer="21"/>
<rectangle x1="0.889" y1="-4.699" x2="1.651" y2="-2.921" layer="51"/>
<rectangle x1="3.429" y1="-2.921" x2="4.191" y2="-1.905" layer="21"/>
<rectangle x1="5.969" y1="-2.921" x2="6.731" y2="-1.905" layer="21"/>
<rectangle x1="3.429" y1="-5.461" x2="4.191" y2="-4.699" layer="21"/>
<rectangle x1="3.429" y1="-4.699" x2="4.191" y2="-2.921" layer="51"/>
<rectangle x1="5.969" y1="-4.699" x2="6.731" y2="-2.921" layer="51"/>
<rectangle x1="5.969" y1="-5.461" x2="6.731" y2="-4.699" layer="21"/>
<rectangle x1="8.509" y1="-2.921" x2="9.271" y2="-1.905" layer="21"/>
<rectangle x1="11.049" y1="-2.921" x2="11.811" y2="-1.905" layer="21"/>
<rectangle x1="8.509" y1="-5.461" x2="9.271" y2="-4.699" layer="21"/>
<rectangle x1="8.509" y1="-4.699" x2="9.271" y2="-2.921" layer="51"/>
<rectangle x1="11.049" y1="-4.699" x2="11.811" y2="-2.921" layer="51"/>
<rectangle x1="11.049" y1="-5.461" x2="11.811" y2="-4.699" layer="21"/>
<rectangle x1="13.589" y1="-2.921" x2="14.351" y2="-1.905" layer="21"/>
<rectangle x1="13.589" y1="-5.461" x2="14.351" y2="-4.699" layer="21"/>
<rectangle x1="13.589" y1="-4.699" x2="14.351" y2="-2.921" layer="51"/>
<rectangle x1="16.129" y1="-2.921" x2="16.891" y2="-1.905" layer="21"/>
<rectangle x1="18.669" y1="-2.921" x2="19.431" y2="-1.905" layer="21"/>
<rectangle x1="16.129" y1="-5.461" x2="16.891" y2="-4.699" layer="21"/>
<rectangle x1="16.129" y1="-4.699" x2="16.891" y2="-2.921" layer="51"/>
<rectangle x1="18.669" y1="-4.699" x2="19.431" y2="-2.921" layer="51"/>
<rectangle x1="18.669" y1="-5.461" x2="19.431" y2="-4.699" layer="21"/>
<rectangle x1="21.209" y1="-2.921" x2="21.971" y2="-1.905" layer="21"/>
<rectangle x1="21.209" y1="-5.461" x2="21.971" y2="-4.699" layer="21"/>
<rectangle x1="21.209" y1="-4.699" x2="21.971" y2="-2.921" layer="51"/>
</package>
<package name="2X05">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-6.35" y1="-1.905" x2="-5.715" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-2.54" x2="-3.81" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-1.905" x2="-3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-2.54" x2="-1.27" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-1.905" x2="-0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-2.54" x2="1.27" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-1.905" x2="1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-2.54" x2="3.81" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="-1.905" x2="-6.35" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="1.905" x2="-5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.54" x2="-4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="-3.81" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="1.905" x2="-3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="2.54" x2="-1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="2.54" x2="-1.27" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="1.905" x2="-0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="2.54" x2="0.635" y2="2.54" width="0.1524" layer="21"/>
<wire x1="0.635" y1="2.54" x2="1.27" y2="1.905" width="0.1524" layer="21"/>
<wire x1="1.27" y1="1.905" x2="1.905" y2="2.54" width="0.1524" layer="21"/>
<wire x1="1.905" y1="2.54" x2="3.175" y2="2.54" width="0.1524" layer="21"/>
<wire x1="3.175" y1="2.54" x2="3.81" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="1.905" x2="-3.81" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="1.905" x2="-1.27" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="1.27" y1="1.905" x2="1.27" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="3.81" y1="1.905" x2="3.81" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="3.175" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-2.54" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-2.54" x2="-1.905" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.54" x2="-4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="3.81" y1="-1.905" x2="4.445" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-2.54" x2="6.35" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="3.81" y1="1.905" x2="4.445" y2="2.54" width="0.1524" layer="21"/>
<wire x1="4.445" y1="2.54" x2="5.715" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.715" y1="2.54" x2="6.35" y2="1.905" width="0.1524" layer="21"/>
<wire x1="6.35" y1="1.905" x2="6.35" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="5.715" y2="-2.54" width="0.1524" layer="21"/>
<pad name="1" x="-5.08" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="2" x="-5.08" y="1.27" drill="1.016" shape="octagon"/>
<pad name="3" x="-2.54" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="4" x="-2.54" y="1.27" drill="1.016" shape="octagon"/>
<pad name="5" x="0" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="6" x="0" y="1.27" drill="1.016" shape="octagon"/>
<pad name="7" x="2.54" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="8" x="2.54" y="1.27" drill="1.016" shape="octagon"/>
<pad name="9" x="5.08" y="-1.27" drill="1.016" shape="octagon"/>
<pad name="10" x="5.08" y="1.27" drill="1.016" shape="octagon"/>
<text x="-6.35" y="3.175" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.35" y="-4.445" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-5.334" y1="-1.524" x2="-4.826" y2="-1.016" layer="51"/>
<rectangle x1="-5.334" y1="1.016" x2="-4.826" y2="1.524" layer="51"/>
<rectangle x1="-2.794" y1="1.016" x2="-2.286" y2="1.524" layer="51"/>
<rectangle x1="-2.794" y1="-1.524" x2="-2.286" y2="-1.016" layer="51"/>
<rectangle x1="-0.254" y1="1.016" x2="0.254" y2="1.524" layer="51"/>
<rectangle x1="-0.254" y1="-1.524" x2="0.254" y2="-1.016" layer="51"/>
<rectangle x1="2.286" y1="1.016" x2="2.794" y2="1.524" layer="51"/>
<rectangle x1="2.286" y1="-1.524" x2="2.794" y2="-1.016" layer="51"/>
<rectangle x1="4.826" y1="1.016" x2="5.334" y2="1.524" layer="51"/>
<rectangle x1="4.826" y1="-1.524" x2="5.334" y2="-1.016" layer="51"/>
</package>
<package name="2X05/90">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-6.35" y1="-1.905" x2="-3.81" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-1.905" x2="-3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-6.35" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="0.635" x2="-6.35" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="6.985" x2="-5.08" y2="1.27" width="0.762" layer="21"/>
<wire x1="-3.81" y1="-1.905" x2="-1.27" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="-1.905" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="6.985" x2="-2.54" y2="1.27" width="0.762" layer="21"/>
<wire x1="-1.27" y1="-1.905" x2="1.27" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-1.905" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="-1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="6.985" x2="0" y2="1.27" width="0.762" layer="21"/>
<wire x1="1.27" y1="-1.905" x2="3.81" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="3.81" y1="-1.905" x2="3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="0.635" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="6.985" x2="2.54" y2="1.27" width="0.762" layer="21"/>
<wire x1="3.81" y1="-1.905" x2="6.35" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="6.35" y1="-1.905" x2="6.35" y2="0.635" width="0.1524" layer="21"/>
<wire x1="6.35" y1="0.635" x2="3.81" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="6.985" x2="5.08" y2="1.27" width="0.762" layer="21"/>
<pad name="2" x="-5.08" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="4" x="-2.54" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="6" x="0" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="8" x="2.54" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="10" x="5.08" y="-3.81" drill="1.016" shape="octagon"/>
<pad name="1" x="-5.08" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="3" x="-2.54" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="5" x="0" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="7" x="2.54" y="-6.35" drill="1.016" shape="octagon"/>
<pad name="9" x="5.08" y="-6.35" drill="1.016" shape="octagon"/>
<text x="-6.985" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="8.255" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-5.461" y1="0.635" x2="-4.699" y2="1.143" layer="21"/>
<rectangle x1="-2.921" y1="0.635" x2="-2.159" y2="1.143" layer="21"/>
<rectangle x1="-0.381" y1="0.635" x2="0.381" y2="1.143" layer="21"/>
<rectangle x1="2.159" y1="0.635" x2="2.921" y2="1.143" layer="21"/>
<rectangle x1="4.699" y1="0.635" x2="5.461" y2="1.143" layer="21"/>
<rectangle x1="-5.461" y1="-2.921" x2="-4.699" y2="-1.905" layer="21"/>
<rectangle x1="-2.921" y1="-2.921" x2="-2.159" y2="-1.905" layer="21"/>
<rectangle x1="-5.461" y1="-5.461" x2="-4.699" y2="-4.699" layer="21"/>
<rectangle x1="-5.461" y1="-4.699" x2="-4.699" y2="-2.921" layer="51"/>
<rectangle x1="-2.921" y1="-4.699" x2="-2.159" y2="-2.921" layer="51"/>
<rectangle x1="-2.921" y1="-5.461" x2="-2.159" y2="-4.699" layer="21"/>
<rectangle x1="-0.381" y1="-2.921" x2="0.381" y2="-1.905" layer="21"/>
<rectangle x1="2.159" y1="-2.921" x2="2.921" y2="-1.905" layer="21"/>
<rectangle x1="-0.381" y1="-5.461" x2="0.381" y2="-4.699" layer="21"/>
<rectangle x1="-0.381" y1="-4.699" x2="0.381" y2="-2.921" layer="51"/>
<rectangle x1="2.159" y1="-4.699" x2="2.921" y2="-2.921" layer="51"/>
<rectangle x1="2.159" y1="-5.461" x2="2.921" y2="-4.699" layer="21"/>
<rectangle x1="4.699" y1="-2.921" x2="5.461" y2="-1.905" layer="21"/>
<rectangle x1="4.699" y1="-5.461" x2="5.461" y2="-4.699" layer="21"/>
<rectangle x1="4.699" y1="-4.699" x2="5.461" y2="-2.921" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="PINH2X2">
<wire x1="-8.89" y1="-2.54" x2="6.35" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="6.35" y1="-2.54" x2="6.35" y2="5.08" width="0.4064" layer="94"/>
<wire x1="6.35" y1="5.08" x2="-8.89" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-8.89" y1="5.08" x2="-8.89" y2="-2.54" width="0.4064" layer="94"/>
<text x="-8.89" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="-8.89" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-5.08" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="3" x="-5.08" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="2.54" y="0" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
</symbol>
<symbol name="PINH2X8">
<wire x1="-6.35" y1="-12.7" x2="8.89" y2="-12.7" width="0.4064" layer="94"/>
<wire x1="8.89" y1="-12.7" x2="8.89" y2="10.16" width="0.4064" layer="94"/>
<wire x1="8.89" y1="10.16" x2="-6.35" y2="10.16" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="10.16" x2="-6.35" y2="-12.7" width="0.4064" layer="94"/>
<text x="-6.35" y="10.795" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-15.24" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="5.08" y="7.62" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="3" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="5.08" y="5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="5" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="6" x="5.08" y="2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="7" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="8" x="5.08" y="0" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="9" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="10" x="5.08" y="-2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="11" x="-2.54" y="-5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="12" x="5.08" y="-5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="13" x="-2.54" y="-7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="14" x="5.08" y="-7.62" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="15" x="-2.54" y="-10.16" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="16" x="5.08" y="-10.16" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
</symbol>
<symbol name="PINH2X18">
<wire x1="-6.35" y1="-25.4" x2="8.89" y2="-25.4" width="0.4064" layer="94"/>
<wire x1="8.89" y1="-25.4" x2="8.89" y2="22.86" width="0.4064" layer="94"/>
<wire x1="8.89" y1="22.86" x2="-6.35" y2="22.86" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="22.86" x2="-6.35" y2="-25.4" width="0.4064" layer="94"/>
<text x="-6.35" y="23.495" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-27.94" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="20.32" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="5.08" y="20.32" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="3" x="-2.54" y="17.78" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="5.08" y="17.78" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="5" x="-2.54" y="15.24" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="6" x="5.08" y="15.24" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="7" x="-2.54" y="12.7" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="8" x="5.08" y="12.7" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="9" x="-2.54" y="10.16" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="10" x="5.08" y="10.16" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="11" x="-2.54" y="7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="12" x="5.08" y="7.62" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="13" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="14" x="5.08" y="5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="15" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="16" x="5.08" y="2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="17" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="18" x="5.08" y="0" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="19" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="20" x="5.08" y="-2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="21" x="-2.54" y="-5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="22" x="5.08" y="-5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="23" x="-2.54" y="-7.62" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="24" x="5.08" y="-7.62" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="25" x="-2.54" y="-10.16" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="26" x="5.08" y="-10.16" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="27" x="-2.54" y="-12.7" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="28" x="5.08" y="-12.7" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="29" x="-2.54" y="-15.24" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="30" x="5.08" y="-15.24" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="31" x="-2.54" y="-17.78" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="32" x="5.08" y="-17.78" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="33" x="-2.54" y="-20.32" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="34" x="5.08" y="-20.32" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="35" x="-2.54" y="-22.86" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="36" x="5.08" y="-22.86" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
</symbol>
<symbol name="PINH2X5">
<wire x1="-6.35" y1="-7.62" x2="8.89" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="8.89" y1="-7.62" x2="8.89" y2="7.62" width="0.4064" layer="94"/>
<wire x1="8.89" y1="7.62" x2="-6.35" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="7.62" x2="-6.35" y2="-7.62" width="0.4064" layer="94"/>
<text x="-6.35" y="8.255" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="5.08" y="5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="3" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="5.08" y="2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="5" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="6" x="5.08" y="0" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="7" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="8" x="5.08" y="-2.54" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
<pin name="9" x="-2.54" y="-5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="10" x="5.08" y="-5.08" visible="pad" length="short" direction="pas" function="dot" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PINHD-2X2" prefix="JP" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINH2X2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2X02">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="/90" package="2X02/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-2X8" prefix="JP" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINH2X8" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2X08">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="/90" package="2X08/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-2X18" prefix="JP" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINH2X18" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2X18">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="17" pad="17"/>
<connect gate="A" pin="18" pad="18"/>
<connect gate="A" pin="19" pad="19"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="20" pad="20"/>
<connect gate="A" pin="21" pad="21"/>
<connect gate="A" pin="22" pad="22"/>
<connect gate="A" pin="23" pad="23"/>
<connect gate="A" pin="24" pad="24"/>
<connect gate="A" pin="25" pad="25"/>
<connect gate="A" pin="26" pad="26"/>
<connect gate="A" pin="27" pad="27"/>
<connect gate="A" pin="28" pad="28"/>
<connect gate="A" pin="29" pad="29"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="30" pad="30"/>
<connect gate="A" pin="31" pad="31"/>
<connect gate="A" pin="32" pad="32"/>
<connect gate="A" pin="33" pad="33"/>
<connect gate="A" pin="34" pad="34"/>
<connect gate="A" pin="35" pad="35"/>
<connect gate="A" pin="36" pad="36"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="/90" package="2X18/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="11" pad="11"/>
<connect gate="A" pin="12" pad="12"/>
<connect gate="A" pin="13" pad="13"/>
<connect gate="A" pin="14" pad="14"/>
<connect gate="A" pin="15" pad="15"/>
<connect gate="A" pin="16" pad="16"/>
<connect gate="A" pin="17" pad="17"/>
<connect gate="A" pin="18" pad="18"/>
<connect gate="A" pin="19" pad="19"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="20" pad="20"/>
<connect gate="A" pin="21" pad="21"/>
<connect gate="A" pin="22" pad="22"/>
<connect gate="A" pin="23" pad="23"/>
<connect gate="A" pin="24" pad="24"/>
<connect gate="A" pin="25" pad="25"/>
<connect gate="A" pin="26" pad="26"/>
<connect gate="A" pin="27" pad="27"/>
<connect gate="A" pin="28" pad="28"/>
<connect gate="A" pin="29" pad="29"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="30" pad="30"/>
<connect gate="A" pin="31" pad="31"/>
<connect gate="A" pin="32" pad="32"/>
<connect gate="A" pin="33" pad="33"/>
<connect gate="A" pin="34" pad="34"/>
<connect gate="A" pin="35" pad="35"/>
<connect gate="A" pin="36" pad="36"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-2X5" prefix="JP" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINH2X5" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2X05">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="/90" package="2X05/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="10" pad="10"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
<connect gate="A" pin="5" pad="5"/>
<connect gate="A" pin="6" pad="6"/>
<connect gate="A" pin="7" pad="7"/>
<connect gate="A" pin="8" pad="8"/>
<connect gate="A" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="dawid">
<description>Dawid Pilawa - IC Library</description>
<packages>
<package name="DIL28-3">
<description>&lt;b&gt;Dual In Line Package Small&lt;/b&gt;</description>
<wire x1="17.78" y1="2.921" x2="-17.78" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="-2.921" x2="17.78" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="17.78" y1="2.921" x2="17.78" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="2.921" x2="-17.78" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="-2.921" x2="-17.78" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-17.78" y1="1.016" x2="-17.78" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-16.51" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-13.97" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="-1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-11.43" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="-3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="-6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="11.43" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="13.97" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="16.51" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="16.51" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="13.97" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="17" x="11.43" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="18" x="8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="19" x="6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="20" x="3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="21" x="1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="22" x="-1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="23" x="-3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="24" x="-6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="25" x="-8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="26" x="-11.43" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="27" x="-13.97" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="28" x="-16.51" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-18.034" y="-2.921" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-8.509" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="PWRN">
<text x="-1.27" y="-0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="0.635" y="-3.81" size="0.8128" layer="97" ratio="1" rot="R270">GND</text>
<text x="0.635" y="6.35" size="0.8128" layer="97" ratio="1" rot="R270">VCC</text>
<pin name="GND" x="0" y="-7.62" visible="off" length="middle" direction="pwr" rot="R90"/>
<pin name="VCC" x="0" y="7.62" visible="off" length="middle" direction="pwr" rot="R270"/>
</symbol>
<symbol name="MT5C6408">
<wire x1="-7.62" y1="22.86" x2="-7.62" y2="-25.4" width="0.4064" layer="94"/>
<wire x1="7.62" y1="-25.4" x2="-7.62" y2="-25.4" width="0.4064" layer="94"/>
<wire x1="7.62" y1="-25.4" x2="7.62" y2="22.86" width="0.4064" layer="94"/>
<wire x1="-7.62" y1="22.86" x2="7.62" y2="22.86" width="0.4064" layer="94"/>
<text x="-7.62" y="-27.94" size="1.778" layer="96">&gt;VALUE</text>
<text x="-7.62" y="23.495" size="1.778" layer="95">&gt;NAME</text>
<pin name="A0" x="-12.7" y="20.32" length="middle" direction="in"/>
<pin name="A1" x="-12.7" y="17.78" length="middle" direction="in"/>
<pin name="A2" x="-12.7" y="15.24" length="middle" direction="in"/>
<pin name="A3" x="-12.7" y="12.7" length="middle" direction="in"/>
<pin name="A4" x="-12.7" y="10.16" length="middle" direction="in"/>
<pin name="A5" x="-12.7" y="7.62" length="middle" direction="in"/>
<pin name="A6" x="-12.7" y="5.08" length="middle" direction="in"/>
<pin name="A7" x="-12.7" y="2.54" length="middle" direction="in"/>
<pin name="A8" x="-12.7" y="0" length="middle" direction="in"/>
<pin name="DQ1" x="12.7" y="20.32" length="middle" rot="R180"/>
<pin name="DQ2" x="12.7" y="17.78" length="middle" rot="R180"/>
<pin name="DQ3" x="12.7" y="15.24" length="middle" rot="R180"/>
<pin name="DQ4" x="12.7" y="12.7" length="middle" rot="R180"/>
<pin name="DQ5" x="12.7" y="10.16" length="middle" rot="R180"/>
<pin name="DQ6" x="12.7" y="7.62" length="middle" rot="R180"/>
<pin name="DQ7" x="12.7" y="5.08" length="middle" rot="R180"/>
<pin name="DQ8" x="12.7" y="2.54" length="middle" rot="R180"/>
<pin name="A9" x="-12.7" y="-2.54" length="middle" direction="in"/>
<pin name="A10" x="-12.7" y="-5.08" length="middle" direction="in"/>
<pin name="A11" x="-12.7" y="-7.62" length="middle" direction="in"/>
<pin name="!CE1" x="-12.7" y="-15.24" length="middle" direction="in"/>
<pin name="!OE" x="-12.7" y="-20.32" length="middle" direction="in"/>
<pin name="!WE" x="-12.7" y="-22.86" length="middle" direction="in"/>
<pin name="CE2" x="-12.7" y="-17.78" length="middle" direction="in"/>
<pin name="A12" x="-12.7" y="-10.16" length="middle" direction="in"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MT5C6408" prefix="IC">
<description>8K x 8 SRAM SRAM MEMORY ARRAY</description>
<gates>
<gate name="P" symbol="PWRN" x="-10.16" y="0" addlevel="request"/>
<gate name="G$1" symbol="MT5C6408" x="12.7" y="0" swaplevel="1"/>
</gates>
<devices>
<device name="" package="DIL28-3">
<connects>
<connect gate="G$1" pin="!CE1" pad="20"/>
<connect gate="G$1" pin="!OE" pad="22"/>
<connect gate="G$1" pin="!WE" pad="27"/>
<connect gate="G$1" pin="A0" pad="10"/>
<connect gate="G$1" pin="A1" pad="9"/>
<connect gate="G$1" pin="A10" pad="21"/>
<connect gate="G$1" pin="A11" pad="23"/>
<connect gate="G$1" pin="A12" pad="2"/>
<connect gate="G$1" pin="A2" pad="8"/>
<connect gate="G$1" pin="A3" pad="7"/>
<connect gate="G$1" pin="A4" pad="6"/>
<connect gate="G$1" pin="A5" pad="5"/>
<connect gate="G$1" pin="A6" pad="4"/>
<connect gate="G$1" pin="A7" pad="3"/>
<connect gate="G$1" pin="A8" pad="25"/>
<connect gate="G$1" pin="A9" pad="24"/>
<connect gate="G$1" pin="CE2" pad="26"/>
<connect gate="G$1" pin="DQ1" pad="11"/>
<connect gate="G$1" pin="DQ2" pad="12"/>
<connect gate="G$1" pin="DQ3" pad="13"/>
<connect gate="G$1" pin="DQ4" pad="15"/>
<connect gate="G$1" pin="DQ5" pad="16"/>
<connect gate="G$1" pin="DQ6" pad="17"/>
<connect gate="G$1" pin="DQ7" pad="18"/>
<connect gate="G$1" pin="DQ8" pad="19"/>
<connect gate="P" pin="GND" pad="14"/>
<connect gate="P" pin="VCC" pad="28"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="74xx-eu">
<description>&lt;b&gt;TTL Devices, 74xx Series with European Symbols&lt;/b&gt;&lt;p&gt;
Based on the following sources:
&lt;ul&gt;
&lt;li&gt;Texas Instruments &lt;i&gt;TTL Data Book&lt;/i&gt;&amp;nbsp;&amp;nbsp;&amp;nbsp;Volume 1, 1996.
&lt;li&gt;TTL Data Book, Volume 2 , 1993
&lt;li&gt;National Seminconductor Databook 1990, ALS/LS Logic
&lt;li&gt;ttl 74er digital data dictionary, ECA Electronic + Acustic GmbH, ISBN 3-88109-032-0
&lt;li&gt;http://icmaster.com/ViewCompare.asp
&lt;/ul&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DIL14">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="8.89" y1="2.921" x2="-8.89" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-2.921" x2="8.89" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="8.89" y1="2.921" x2="8.89" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="2.921" x2="-8.89" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="-2.921" x2="-8.89" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-8.89" y1="1.016" x2="-8.89" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-7.62" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-5.08" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="7.62" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="7.62" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-2.54" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="0" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="5.08" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="2.54" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="5.08" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="2.54" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="0" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="-2.54" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="-5.08" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="-7.62" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-9.271" y="-3.048" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-6.731" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SO14">
<description>&lt;b&gt;Small Outline package&lt;/b&gt; 150 mil</description>
<wire x1="4.064" y1="1.9558" x2="-4.064" y2="1.9558" width="0.1524" layer="51"/>
<wire x1="4.064" y1="-1.9558" x2="4.445" y2="-1.5748" width="0.1524" layer="21" curve="90"/>
<wire x1="-4.445" y1="1.5748" x2="-4.064" y2="1.9558" width="0.1524" layer="21" curve="-90"/>
<wire x1="4.064" y1="1.9558" x2="4.445" y2="1.5748" width="0.1524" layer="21" curve="-90"/>
<wire x1="-4.445" y1="-1.5748" x2="-4.064" y2="-1.9558" width="0.1524" layer="21" curve="90"/>
<wire x1="-4.064" y1="-1.9558" x2="4.064" y2="-1.9558" width="0.1524" layer="51"/>
<wire x1="4.445" y1="-1.5748" x2="4.445" y2="1.5748" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.5748" x2="-4.445" y2="0.508" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="0.508" x2="-4.445" y2="-0.508" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-0.508" x2="-4.445" y2="-1.5748" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="0.508" x2="-4.445" y2="-0.508" width="0.1524" layer="21" curve="-180"/>
<wire x1="-4.445" y1="-1.6002" x2="4.445" y2="-1.6002" width="0.0508" layer="21"/>
<smd name="1" x="-3.81" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="14" x="-3.81" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="2" x="-2.54" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="3" x="-1.27" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="13" x="-2.54" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="12" x="-1.27" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="4" x="0" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="11" x="0" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="5" x="1.27" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="6" x="2.54" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="10" x="1.27" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="9" x="2.54" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="7" x="3.81" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="8" x="3.81" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<text x="-3.175" y="-0.762" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-4.826" y="-1.905" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<rectangle x1="-0.254" y1="1.9558" x2="0.254" y2="3.0988" layer="51"/>
<rectangle x1="-4.064" y1="-3.0988" x2="-3.556" y2="-1.9558" layer="51"/>
<rectangle x1="-2.794" y1="-3.0988" x2="-2.286" y2="-1.9558" layer="51"/>
<rectangle x1="-1.524" y1="-3.0734" x2="-1.016" y2="-1.9304" layer="51"/>
<rectangle x1="-0.254" y1="-3.0988" x2="0.254" y2="-1.9558" layer="51"/>
<rectangle x1="-1.524" y1="1.9558" x2="-1.016" y2="3.0988" layer="51"/>
<rectangle x1="-2.794" y1="1.9558" x2="-2.286" y2="3.0988" layer="51"/>
<rectangle x1="-4.064" y1="1.9558" x2="-3.556" y2="3.0988" layer="51"/>
<rectangle x1="1.016" y1="1.9558" x2="1.524" y2="3.0988" layer="51"/>
<rectangle x1="2.286" y1="1.9558" x2="2.794" y2="3.0988" layer="51"/>
<rectangle x1="3.556" y1="1.9558" x2="4.064" y2="3.0988" layer="51"/>
<rectangle x1="1.016" y1="-3.0988" x2="1.524" y2="-1.9558" layer="51"/>
<rectangle x1="2.286" y1="-3.0988" x2="2.794" y2="-1.9558" layer="51"/>
<rectangle x1="3.556" y1="-3.0988" x2="4.064" y2="-1.9558" layer="51"/>
</package>
<package name="LCC20">
<description>&lt;b&gt;Leadless Chip Carrier&lt;/b&gt;&lt;p&gt; Ceramic Package</description>
<wire x1="-0.4001" y1="4.4" x2="-0.87" y2="4.4" width="0.2032" layer="51"/>
<wire x1="-3.3" y1="4.4" x2="-4.4" y2="3.3" width="0.2032" layer="51"/>
<wire x1="-0.4001" y1="4.3985" x2="0.4001" y2="4.3985" width="0.2032" layer="51" curve="180"/>
<wire x1="-1.6701" y1="4.3985" x2="-0.8699" y2="4.3985" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.3985" y1="2.14" x2="-4.3985" y2="2.94" width="0.2032" layer="51" curve="180"/>
<wire x1="-2.9401" y1="4.4" x2="-3.3" y2="4.4" width="0.2032" layer="51"/>
<wire x1="0.87" y1="4.4" x2="0.4001" y2="4.4" width="0.2032" layer="51"/>
<wire x1="0.87" y1="4.3985" x2="1.67" y2="4.3985" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.4" y1="3.3" x2="-4.4" y2="2.9401" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="2.14" x2="-4.4" y2="1.6701" width="0.2032" layer="51"/>
<wire x1="-4.3985" y1="0.87" x2="-4.3985" y2="1.67" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.3985" y1="-0.4001" x2="-4.3985" y2="0.4001" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.3985" y1="-1.6701" x2="-4.3985" y2="-0.8699" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.4" y1="0.87" x2="-4.4" y2="0.4001" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="-0.4001" x2="-4.4" y2="-0.87" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="-2.9401" x2="-4.4" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="-4.4" x2="-4.4" y2="-4.4099" width="0.2032" layer="51"/>
<wire x1="2.14" y1="4.3985" x2="2.94" y2="4.3985" width="0.2032" layer="51" curve="180"/>
<wire x1="2.14" y1="4.4" x2="1.6701" y2="4.4" width="0.2032" layer="51"/>
<wire x1="4.4" y1="4.4" x2="2.9401" y2="4.4" width="0.2032" layer="51"/>
<wire x1="0.4001" y1="-4.4" x2="0.87" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-0.4001" y1="-4.3985" x2="0.4001" y2="-4.3985" width="0.2032" layer="51" curve="-180"/>
<wire x1="0.87" y1="-4.3985" x2="1.67" y2="-4.3985" width="0.2032" layer="51" curve="-180"/>
<wire x1="2.9401" y1="-4.4" x2="4.4" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-0.87" y1="-4.4" x2="-0.4001" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-1.6701" y1="-4.3985" x2="-0.8699" y2="-4.3985" width="0.2032" layer="51" curve="-180"/>
<wire x1="-2.9401" y1="-4.3985" x2="-2.1399" y2="-4.3985" width="0.2032" layer="51" curve="-180"/>
<wire x1="-2.14" y1="-4.4" x2="-1.6701" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="-4.4" y1="-4.4" x2="-2.9401" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="4.4" y1="0.4001" x2="4.4" y2="0.87" width="0.2032" layer="51"/>
<wire x1="4.3985" y1="0.4001" x2="4.3985" y2="-0.4001" width="0.2032" layer="51" curve="180"/>
<wire x1="4.3985" y1="1.6701" x2="4.3985" y2="0.8699" width="0.2032" layer="51" curve="180"/>
<wire x1="4.4" y1="2.9401" x2="4.4" y2="4.4" width="0.2032" layer="51"/>
<wire x1="4.4" y1="-0.87" x2="4.4" y2="-0.4001" width="0.2032" layer="51"/>
<wire x1="4.3985" y1="-0.87" x2="4.3985" y2="-1.67" width="0.2032" layer="51" curve="180"/>
<wire x1="4.3985" y1="-2.14" x2="4.3985" y2="-2.94" width="0.2032" layer="51" curve="180"/>
<wire x1="4.4" y1="-2.14" x2="4.4" y2="-1.6701" width="0.2032" layer="51"/>
<wire x1="4.4" y1="-4.4" x2="4.4" y2="-2.9401" width="0.2032" layer="51"/>
<wire x1="-2.9401" y1="4.3985" x2="-2.1399" y2="4.3985" width="0.2032" layer="51" curve="180"/>
<wire x1="-1.6701" y1="4.4" x2="-2.14" y2="4.4" width="0.2032" layer="51"/>
<wire x1="-4.3985" y1="-2.9401" x2="-4.3985" y2="-2.1399" width="0.2032" layer="51" curve="180"/>
<wire x1="-4.4" y1="-1.6701" x2="-4.4" y2="-2.14" width="0.2032" layer="51"/>
<wire x1="1.6701" y1="-4.4" x2="2.14" y2="-4.4" width="0.2032" layer="51"/>
<wire x1="2.14" y1="-4.3985" x2="2.94" y2="-4.3985" width="0.2032" layer="51" curve="-180"/>
<wire x1="4.3985" y1="2.9401" x2="4.3985" y2="2.1399" width="0.2032" layer="51" curve="180"/>
<wire x1="4.4" y1="1.6701" x2="4.4" y2="2.14" width="0.2032" layer="51"/>
<wire x1="-3.3" y1="4.4" x2="-4.4" y2="3.3" width="0.2032" layer="21"/>
<wire x1="-4.4" y1="-3.1941" x2="-4.4" y2="-4.4" width="0.2032" layer="21"/>
<wire x1="-4.4" y1="-4.4" x2="-3.1941" y2="-4.4" width="0.2032" layer="21"/>
<wire x1="3.1941" y1="-4.4" x2="4.4" y2="-4.4" width="0.2032" layer="21"/>
<wire x1="4.4" y1="-4.4" x2="4.4" y2="-3.1941" width="0.2032" layer="21"/>
<wire x1="4.4" y1="3.1941" x2="4.4" y2="4.4" width="0.2032" layer="21"/>
<wire x1="4.4" y1="4.4" x2="3.1941" y2="4.4" width="0.2032" layer="21"/>
<smd name="2" x="-1.27" y="4.5001" dx="0.8" dy="2" layer="1"/>
<smd name="1" x="0" y="3.8001" dx="0.8" dy="3.4" layer="1"/>
<smd name="3" x="-2.54" y="4.5001" dx="0.8" dy="2" layer="1"/>
<smd name="4" x="-4.5001" y="2.54" dx="2" dy="0.8" layer="1"/>
<smd name="5" x="-4.5001" y="1.27" dx="2" dy="0.8" layer="1"/>
<smd name="6" x="-4.5001" y="0" dx="2" dy="0.8" layer="1"/>
<smd name="7" x="-4.5001" y="-1.27" dx="2" dy="0.8" layer="1"/>
<smd name="8" x="-4.5001" y="-2.54" dx="2" dy="0.8" layer="1"/>
<smd name="9" x="-2.54" y="-4.5001" dx="0.8" dy="2" layer="1"/>
<smd name="10" x="-1.27" y="-4.5001" dx="0.8" dy="2" layer="1"/>
<smd name="11" x="0" y="-4.5001" dx="0.8" dy="2" layer="1"/>
<smd name="12" x="1.27" y="-4.5001" dx="0.8" dy="2" layer="1"/>
<smd name="13" x="2.54" y="-4.5001" dx="0.8" dy="2" layer="1"/>
<smd name="14" x="4.5001" y="-2.54" dx="2" dy="0.8" layer="1"/>
<smd name="15" x="4.5001" y="-1.27" dx="2" dy="0.8" layer="1"/>
<smd name="16" x="4.5001" y="0" dx="2" dy="0.8" layer="1"/>
<smd name="17" x="4.5001" y="1.27" dx="2" dy="0.8" layer="1"/>
<smd name="18" x="4.5001" y="2.54" dx="2" dy="0.8" layer="1"/>
<smd name="19" x="2.54" y="4.5001" dx="0.8" dy="2" layer="1"/>
<smd name="20" x="1.27" y="4.5001" dx="0.8" dy="2" layer="1"/>
<text x="-4.0051" y="6.065" size="1.778" layer="25">&gt;NAME</text>
<text x="-3.9751" y="-7.5601" size="1.778" layer="27">&gt;VALUE</text>
</package>
<package name="DIL20">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="12.7" y1="2.921" x2="-12.7" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-2.921" x2="12.7" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="12.7" y1="2.921" x2="12.7" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="2.921" x2="-12.7" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="-2.921" x2="-12.7" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-12.7" y1="1.016" x2="-12.7" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-11.43" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="-1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="11.43" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="11.43" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="-1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="17" x="-3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="18" x="-6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="19" x="-8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="20" x="-11.43" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-13.081" y="-3.048" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="-9.779" y="-0.381" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="SO20W">
<description>&lt;b&gt;Wide Small Outline package&lt;/b&gt; 300 mil</description>
<wire x1="6.1214" y1="3.7338" x2="-6.1214" y2="3.7338" width="0.1524" layer="51"/>
<wire x1="6.1214" y1="-3.7338" x2="6.5024" y2="-3.3528" width="0.1524" layer="21" curve="90"/>
<wire x1="-6.5024" y1="3.3528" x2="-6.1214" y2="3.7338" width="0.1524" layer="21" curve="-90"/>
<wire x1="6.1214" y1="3.7338" x2="6.5024" y2="3.3528" width="0.1524" layer="21" curve="-90"/>
<wire x1="-6.5024" y1="-3.3528" x2="-6.1214" y2="-3.7338" width="0.1524" layer="21" curve="90"/>
<wire x1="-6.1214" y1="-3.7338" x2="6.1214" y2="-3.7338" width="0.1524" layer="51"/>
<wire x1="6.5024" y1="-3.3528" x2="6.5024" y2="3.3528" width="0.1524" layer="21"/>
<wire x1="-6.5024" y1="3.3528" x2="-6.5024" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-6.5024" y1="1.27" x2="-6.5024" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-6.5024" y1="-1.27" x2="-6.5024" y2="-3.3528" width="0.1524" layer="21"/>
<wire x1="-6.477" y1="-3.3782" x2="6.477" y2="-3.3782" width="0.0508" layer="21"/>
<wire x1="-6.5024" y1="1.27" x2="-6.5024" y2="-1.27" width="0.1524" layer="21" curve="-180"/>
<smd name="1" x="-5.715" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="2" x="-4.445" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="3" x="-3.175" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="4" x="-1.905" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="5" x="-0.635" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="6" x="0.635" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="7" x="1.905" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="8" x="3.175" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="13" x="3.175" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="14" x="1.905" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="15" x="0.635" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="16" x="-0.635" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="17" x="-1.905" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="18" x="-3.175" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="19" x="-4.445" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="20" x="-5.715" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="9" x="4.445" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="10" x="5.715" y="-5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="12" x="4.445" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<smd name="11" x="5.715" y="5.0292" dx="0.6604" dy="2.032" layer="1"/>
<text x="-3.81" y="-1.778" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-6.858" y="-3.175" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<rectangle x1="-5.969" y1="-3.8608" x2="-5.461" y2="-3.7338" layer="51"/>
<rectangle x1="-5.969" y1="-5.334" x2="-5.461" y2="-3.8608" layer="51"/>
<rectangle x1="-4.699" y1="-3.8608" x2="-4.191" y2="-3.7338" layer="51"/>
<rectangle x1="-4.699" y1="-5.334" x2="-4.191" y2="-3.8608" layer="51"/>
<rectangle x1="-3.429" y1="-3.8608" x2="-2.921" y2="-3.7338" layer="51"/>
<rectangle x1="-3.429" y1="-5.334" x2="-2.921" y2="-3.8608" layer="51"/>
<rectangle x1="-2.159" y1="-3.8608" x2="-1.651" y2="-3.7338" layer="51"/>
<rectangle x1="-2.159" y1="-5.334" x2="-1.651" y2="-3.8608" layer="51"/>
<rectangle x1="-0.889" y1="-5.334" x2="-0.381" y2="-3.8608" layer="51"/>
<rectangle x1="-0.889" y1="-3.8608" x2="-0.381" y2="-3.7338" layer="51"/>
<rectangle x1="0.381" y1="-3.8608" x2="0.889" y2="-3.7338" layer="51"/>
<rectangle x1="0.381" y1="-5.334" x2="0.889" y2="-3.8608" layer="51"/>
<rectangle x1="1.651" y1="-3.8608" x2="2.159" y2="-3.7338" layer="51"/>
<rectangle x1="1.651" y1="-5.334" x2="2.159" y2="-3.8608" layer="51"/>
<rectangle x1="2.921" y1="-3.8608" x2="3.429" y2="-3.7338" layer="51"/>
<rectangle x1="2.921" y1="-5.334" x2="3.429" y2="-3.8608" layer="51"/>
<rectangle x1="-5.969" y1="3.8608" x2="-5.461" y2="5.334" layer="51"/>
<rectangle x1="-5.969" y1="3.7338" x2="-5.461" y2="3.8608" layer="51"/>
<rectangle x1="-4.699" y1="3.7338" x2="-4.191" y2="3.8608" layer="51"/>
<rectangle x1="-4.699" y1="3.8608" x2="-4.191" y2="5.334" layer="51"/>
<rectangle x1="-3.429" y1="3.7338" x2="-2.921" y2="3.8608" layer="51"/>
<rectangle x1="-3.429" y1="3.8608" x2="-2.921" y2="5.334" layer="51"/>
<rectangle x1="-2.159" y1="3.7338" x2="-1.651" y2="3.8608" layer="51"/>
<rectangle x1="-2.159" y1="3.8608" x2="-1.651" y2="5.334" layer="51"/>
<rectangle x1="-0.889" y1="3.7338" x2="-0.381" y2="3.8608" layer="51"/>
<rectangle x1="-0.889" y1="3.8608" x2="-0.381" y2="5.334" layer="51"/>
<rectangle x1="0.381" y1="3.7338" x2="0.889" y2="3.8608" layer="51"/>
<rectangle x1="0.381" y1="3.8608" x2="0.889" y2="5.334" layer="51"/>
<rectangle x1="1.651" y1="3.7338" x2="2.159" y2="3.8608" layer="51"/>
<rectangle x1="1.651" y1="3.8608" x2="2.159" y2="5.334" layer="51"/>
<rectangle x1="2.921" y1="3.7338" x2="3.429" y2="3.8608" layer="51"/>
<rectangle x1="2.921" y1="3.8608" x2="3.429" y2="5.334" layer="51"/>
<rectangle x1="4.191" y1="3.7338" x2="4.699" y2="3.8608" layer="51"/>
<rectangle x1="5.461" y1="3.7338" x2="5.969" y2="3.8608" layer="51"/>
<rectangle x1="4.191" y1="3.8608" x2="4.699" y2="5.334" layer="51"/>
<rectangle x1="5.461" y1="3.8608" x2="5.969" y2="5.334" layer="51"/>
<rectangle x1="4.191" y1="-3.8608" x2="4.699" y2="-3.7338" layer="51"/>
<rectangle x1="5.461" y1="-3.8608" x2="5.969" y2="-3.7338" layer="51"/>
<rectangle x1="4.191" y1="-5.334" x2="4.699" y2="-3.8608" layer="51"/>
<rectangle x1="5.461" y1="-5.334" x2="5.969" y2="-3.8608" layer="51"/>
</package>
<package name="DIL16">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="10.16" y1="2.921" x2="-10.16" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-2.921" x2="10.16" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="10.16" y1="2.921" x2="10.16" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="2.921" x2="-10.16" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-2.921" x2="-10.16" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.016" x2="-10.16" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="-1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="-3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="-6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="-8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-10.541" y="-2.921" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-7.493" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SO16">
<description>&lt;b&gt;Small Outline package&lt;/b&gt; 150 mil</description>
<wire x1="4.699" y1="1.9558" x2="-4.699" y2="1.9558" width="0.1524" layer="51"/>
<wire x1="4.699" y1="-1.9558" x2="5.08" y2="-1.5748" width="0.1524" layer="21" curve="90"/>
<wire x1="-5.08" y1="1.5748" x2="-4.699" y2="1.9558" width="0.1524" layer="21" curve="-90"/>
<wire x1="4.699" y1="1.9558" x2="5.08" y2="1.5748" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.08" y1="-1.5748" x2="-4.699" y2="-1.9558" width="0.1524" layer="21" curve="90"/>
<wire x1="-4.699" y1="-1.9558" x2="4.699" y2="-1.9558" width="0.1524" layer="51"/>
<wire x1="5.08" y1="-1.5748" x2="5.08" y2="1.5748" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.5748" x2="-5.08" y2="0.508" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.508" x2="-5.08" y2="-0.508" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.508" x2="-5.08" y2="-1.5748" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.508" x2="-5.08" y2="-0.508" width="0.1524" layer="21" curve="-180"/>
<wire x1="-5.08" y1="-1.6002" x2="5.08" y2="-1.6002" width="0.0508" layer="21"/>
<smd name="1" x="-4.445" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="16" x="-4.445" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="2" x="-3.175" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="3" x="-1.905" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="15" x="-3.175" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="14" x="-1.905" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="4" x="-0.635" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="13" x="-0.635" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="5" x="0.635" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="12" x="0.635" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="6" x="1.905" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="7" x="3.175" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="11" x="1.905" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="10" x="3.175" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="8" x="4.445" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="9" x="4.445" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<text x="-3.81" y="-0.762" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-5.461" y="-1.905" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<rectangle x1="-0.889" y1="1.9558" x2="-0.381" y2="3.0988" layer="51"/>
<rectangle x1="-4.699" y1="-3.0988" x2="-4.191" y2="-1.9558" layer="51"/>
<rectangle x1="-3.429" y1="-3.0988" x2="-2.921" y2="-1.9558" layer="51"/>
<rectangle x1="-2.159" y1="-3.0734" x2="-1.651" y2="-1.9304" layer="51"/>
<rectangle x1="-0.889" y1="-3.0988" x2="-0.381" y2="-1.9558" layer="51"/>
<rectangle x1="-2.159" y1="1.9558" x2="-1.651" y2="3.0988" layer="51"/>
<rectangle x1="-3.429" y1="1.9558" x2="-2.921" y2="3.0988" layer="51"/>
<rectangle x1="-4.699" y1="1.9558" x2="-4.191" y2="3.0988" layer="51"/>
<rectangle x1="0.381" y1="-3.0988" x2="0.889" y2="-1.9558" layer="51"/>
<rectangle x1="1.651" y1="-3.0988" x2="2.159" y2="-1.9558" layer="51"/>
<rectangle x1="2.921" y1="-3.0988" x2="3.429" y2="-1.9558" layer="51"/>
<rectangle x1="4.191" y1="-3.0988" x2="4.699" y2="-1.9558" layer="51"/>
<rectangle x1="0.381" y1="1.9558" x2="0.889" y2="3.0988" layer="51"/>
<rectangle x1="1.651" y1="1.9558" x2="2.159" y2="3.0988" layer="51"/>
<rectangle x1="2.921" y1="1.9558" x2="3.429" y2="3.0988" layer="51"/>
<rectangle x1="4.191" y1="1.9558" x2="4.699" y2="3.0988" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="7427">
<wire x1="-2.54" y1="5.08" x2="2.54" y2="0" width="0.4064" layer="94" curve="-90" cap="flat"/>
<wire x1="-2.54" y1="-5.08" x2="2.54" y2="0" width="0.4064" layer="94" curve="90" cap="flat"/>
<wire x1="1.778" y1="2.54" x2="-2.54" y2="2.54" width="0.1524" layer="94"/>
<wire x1="1.778" y1="-2.54" x2="-2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94"/>
<text x="2.54" y="3.175" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="I0" x="-7.62" y="2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="I1" x="-7.62" y="0" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="O" x="7.62" y="0" visible="pad" length="middle" direction="out" function="dot" rot="R180"/>
<pin name="I2" x="-7.62" y="-2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
</symbol>
<symbol name="PWRN">
<text x="-0.635" y="-0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.905" y="-5.842" size="1.27" layer="95" rot="R90">GND</text>
<text x="1.905" y="2.54" size="1.27" layer="95" rot="R90">VCC</text>
<pin name="GND" x="0" y="-7.62" visible="pad" length="middle" direction="pwr" rot="R90"/>
<pin name="VCC" x="0" y="7.62" visible="pad" length="middle" direction="pwr" rot="R270"/>
</symbol>
<symbol name="7420">
<wire x1="-2.54" y1="7.62" x2="2.54" y2="2.54" width="0.4064" layer="94" curve="-90"/>
<wire x1="-2.54" y1="-7.62" x2="2.54" y2="-2.54" width="0.4064" layer="94" curve="90"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="7.62" x2="-2.54" y2="-7.62" width="0.4064" layer="94"/>
<text x="3.81" y="5.08" size="1.778" layer="95">&gt;NAME</text>
<text x="3.81" y="-6.985" size="1.778" layer="96">&gt;VALUE</text>
<pin name="I0" x="-7.62" y="5.08" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="I1" x="-7.62" y="2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="I2" x="-7.62" y="-2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="I3" x="-7.62" y="-5.08" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="O" x="7.62" y="0" visible="pad" length="middle" direction="out" function="dot" rot="R180"/>
</symbol>
<symbol name="7408">
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94" curve="-180"/>
<text x="2.54" y="3.175" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="I0" x="-7.62" y="2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="I1" x="-7.62" y="-2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="O" x="7.62" y="0" visible="pad" length="middle" direction="out" rot="R180"/>
</symbol>
<symbol name="74245">
<wire x1="-7.62" y1="-15.24" x2="7.62" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="7.62" y1="-15.24" x2="7.62" y2="15.24" width="0.4064" layer="94"/>
<wire x1="7.62" y1="15.24" x2="-7.62" y2="15.24" width="0.4064" layer="94"/>
<wire x1="-7.62" y1="15.24" x2="-7.62" y2="-15.24" width="0.4064" layer="94"/>
<text x="-7.62" y="15.875" size="1.778" layer="95">&gt;NAME</text>
<text x="-7.62" y="-17.78" size="1.778" layer="96">&gt;VALUE</text>
<pin name="DIR" x="-12.7" y="-10.16" length="middle" direction="in"/>
<pin name="A1" x="-12.7" y="12.7" length="middle"/>
<pin name="A2" x="-12.7" y="10.16" length="middle"/>
<pin name="A3" x="-12.7" y="7.62" length="middle"/>
<pin name="A4" x="-12.7" y="5.08" length="middle"/>
<pin name="A5" x="-12.7" y="2.54" length="middle"/>
<pin name="A6" x="-12.7" y="0" length="middle"/>
<pin name="A7" x="-12.7" y="-2.54" length="middle"/>
<pin name="A8" x="-12.7" y="-5.08" length="middle"/>
<pin name="B8" x="12.7" y="-5.08" length="middle" rot="R180"/>
<pin name="B7" x="12.7" y="-2.54" length="middle" rot="R180"/>
<pin name="B6" x="12.7" y="0" length="middle" rot="R180"/>
<pin name="B5" x="12.7" y="2.54" length="middle" rot="R180"/>
<pin name="B4" x="12.7" y="5.08" length="middle" rot="R180"/>
<pin name="B3" x="12.7" y="7.62" length="middle" rot="R180"/>
<pin name="B2" x="12.7" y="10.16" length="middle" rot="R180"/>
<pin name="B1" x="12.7" y="12.7" length="middle" rot="R180"/>
<pin name="G" x="-12.7" y="-12.7" length="middle" direction="in" function="dot"/>
</symbol>
<symbol name="7432">
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94" curve="-180"/>
<wire x1="1.778" y1="2.54" x2="-2.54" y2="2.54" width="0.1524" layer="94"/>
<wire x1="1.778" y1="-2.54" x2="-2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94"/>
<text x="2.54" y="3.175" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="I0" x="-7.62" y="2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="I1" x="-7.62" y="-2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="O" x="7.62" y="0" visible="pad" length="middle" direction="out" rot="R180"/>
</symbol>
<symbol name="74157">
<wire x1="-7.62" y1="-15.24" x2="7.62" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="7.62" y1="-15.24" x2="7.62" y2="15.24" width="0.4064" layer="94"/>
<wire x1="7.62" y1="15.24" x2="-7.62" y2="15.24" width="0.4064" layer="94"/>
<wire x1="-7.62" y1="15.24" x2="-7.62" y2="-15.24" width="0.4064" layer="94"/>
<text x="-7.62" y="15.875" size="1.778" layer="95">&gt;NAME</text>
<text x="-7.62" y="-17.78" size="1.778" layer="96">&gt;VALUE</text>
<pin name="!A!/B" x="-12.7" y="-10.16" length="middle" direction="in"/>
<pin name="1A" x="-12.7" y="12.7" length="middle" direction="in"/>
<pin name="1B" x="-12.7" y="10.16" length="middle" direction="in"/>
<pin name="1Y" x="12.7" y="12.7" length="middle" direction="out" rot="R180"/>
<pin name="2A" x="-12.7" y="7.62" length="middle" direction="in"/>
<pin name="2B" x="-12.7" y="5.08" length="middle" direction="in"/>
<pin name="2Y" x="12.7" y="7.62" length="middle" direction="out" rot="R180"/>
<pin name="3Y" x="12.7" y="2.54" length="middle" direction="out" rot="R180"/>
<pin name="3B" x="-12.7" y="0" length="middle" direction="in"/>
<pin name="3A" x="-12.7" y="2.54" length="middle" direction="in"/>
<pin name="4Y" x="12.7" y="-2.54" length="middle" direction="out" rot="R180"/>
<pin name="4B" x="-12.7" y="-5.08" length="middle" direction="in"/>
<pin name="4A" x="-12.7" y="-2.54" length="middle" direction="in"/>
<pin name="G" x="-12.7" y="-12.7" length="middle" direction="in" function="dot"/>
</symbol>
<symbol name="7404">
<wire x1="-5.08" y1="5.08" x2="5.08" y2="0" width="0.4064" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="5.08" width="0.4064" layer="94"/>
<text x="2.54" y="3.175" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="I" x="-10.16" y="0" visible="pad" length="middle" direction="in"/>
<pin name="O" x="10.16" y="0" visible="pad" length="middle" direction="out" function="dot" rot="R180"/>
</symbol>
<symbol name="7400">
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94" curve="-180"/>
<text x="2.54" y="3.175" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="I0" x="-7.62" y="2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="I1" x="-7.62" y="-2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="O" x="7.62" y="0" visible="pad" length="middle" direction="out" function="dot" rot="R180"/>
</symbol>
<symbol name="7402">
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-5.08" width="0.4064" layer="94" curve="-180"/>
<wire x1="1.778" y1="2.54" x2="-2.54" y2="2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="1.778" y1="-2.54" x2="-2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="-2.54" x2="-2.54" y2="-5.08" width="0.4064" layer="94"/>
<text x="2.54" y="3.175" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="O" x="7.62" y="0" visible="pad" length="middle" direction="out" function="dot" rot="R180"/>
<pin name="I0" x="-7.62" y="2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
<pin name="I1" x="-7.62" y="-2.54" visible="pad" length="middle" direction="in" swaplevel="1"/>
</symbol>
<symbol name="74374">
<wire x1="-7.62" y1="-15.24" x2="7.62" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="7.62" y1="-15.24" x2="7.62" y2="15.24" width="0.4064" layer="94"/>
<wire x1="7.62" y1="15.24" x2="-7.62" y2="15.24" width="0.4064" layer="94"/>
<wire x1="-7.62" y1="15.24" x2="-7.62" y2="-15.24" width="0.4064" layer="94"/>
<text x="-7.62" y="15.875" size="1.778" layer="95">&gt;NAME</text>
<text x="-7.62" y="-17.78" size="1.778" layer="96">&gt;VALUE</text>
<pin name="OC" x="-12.7" y="-10.16" length="middle" direction="in" function="dot"/>
<pin name="1Q" x="12.7" y="12.7" length="middle" direction="hiz" rot="R180"/>
<pin name="1D" x="-12.7" y="12.7" length="middle" direction="in"/>
<pin name="2D" x="-12.7" y="10.16" length="middle" direction="in"/>
<pin name="2Q" x="12.7" y="10.16" length="middle" direction="hiz" rot="R180"/>
<pin name="3Q" x="12.7" y="7.62" length="middle" direction="hiz" rot="R180"/>
<pin name="3D" x="-12.7" y="7.62" length="middle" direction="in"/>
<pin name="4D" x="-12.7" y="5.08" length="middle" direction="in"/>
<pin name="4Q" x="12.7" y="5.08" length="middle" direction="hiz" rot="R180"/>
<pin name="CLK" x="-12.7" y="-12.7" length="middle" direction="in" function="clk"/>
<pin name="5Q" x="12.7" y="2.54" length="middle" direction="hiz" rot="R180"/>
<pin name="5D" x="-12.7" y="2.54" length="middle" direction="in"/>
<pin name="6D" x="-12.7" y="0" length="middle" direction="in"/>
<pin name="6Q" x="12.7" y="0" length="middle" direction="hiz" rot="R180"/>
<pin name="7Q" x="12.7" y="-2.54" length="middle" direction="hiz" rot="R180"/>
<pin name="7D" x="-12.7" y="-2.54" length="middle" direction="in"/>
<pin name="8D" x="-12.7" y="-5.08" length="middle" direction="in"/>
<pin name="8Q" x="12.7" y="-5.08" length="middle" direction="hiz" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="74*27" prefix="IC">
<description>Triple 3-input &lt;b&gt;NOR&lt;/b&gt; gate</description>
<gates>
<gate name="A" symbol="7427" x="20.32" y="0" swaplevel="1"/>
<gate name="B" symbol="7427" x="20.32" y="-12.7" swaplevel="1"/>
<gate name="C" symbol="7427" x="43.18" y="0" swaplevel="1"/>
<gate name="P" symbol="PWRN" x="0" y="-7.62" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="I2" pad="13"/>
<connect gate="A" pin="O" pad="12"/>
<connect gate="B" pin="I0" pad="3"/>
<connect gate="B" pin="I1" pad="4"/>
<connect gate="B" pin="I2" pad="5"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I0" pad="9"/>
<connect gate="C" pin="I1" pad="10"/>
<connect gate="C" pin="I2" pad="11"/>
<connect gate="C" pin="O" pad="8"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
</technologies>
</device>
<device name="D" package="SO14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="I2" pad="13"/>
<connect gate="A" pin="O" pad="12"/>
<connect gate="B" pin="I0" pad="3"/>
<connect gate="B" pin="I1" pad="4"/>
<connect gate="B" pin="I2" pad="5"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I0" pad="9"/>
<connect gate="C" pin="I1" pad="10"/>
<connect gate="C" pin="I2" pad="11"/>
<connect gate="C" pin="O" pad="8"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="I0" pad="2"/>
<connect gate="A" pin="I1" pad="3"/>
<connect gate="A" pin="I2" pad="19"/>
<connect gate="A" pin="O" pad="18"/>
<connect gate="B" pin="I0" pad="4"/>
<connect gate="B" pin="I1" pad="6"/>
<connect gate="B" pin="I2" pad="8"/>
<connect gate="B" pin="O" pad="9"/>
<connect gate="C" pin="I0" pad="13"/>
<connect gate="C" pin="I1" pad="14"/>
<connect gate="C" pin="I2" pad="16"/>
<connect gate="C" pin="O" pad="12"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="74*20" prefix="IC">
<description>Dual 4-input &lt;b&gt;NAND&lt;/b&gt; gate</description>
<gates>
<gate name="A" symbol="7420" x="15.24" y="0" swaplevel="1"/>
<gate name="B" symbol="7420" x="38.1" y="0" swaplevel="1"/>
<gate name="P" symbol="PWRN" x="-7.62" y="0" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="I2" pad="4"/>
<connect gate="A" pin="I3" pad="5"/>
<connect gate="A" pin="O" pad="6"/>
<connect gate="B" pin="I0" pad="9"/>
<connect gate="B" pin="I1" pad="10"/>
<connect gate="B" pin="I2" pad="12"/>
<connect gate="B" pin="I3" pad="13"/>
<connect gate="B" pin="O" pad="8"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="D" package="SO14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="I2" pad="4"/>
<connect gate="A" pin="I3" pad="5"/>
<connect gate="A" pin="O" pad="6"/>
<connect gate="B" pin="I0" pad="9"/>
<connect gate="B" pin="I1" pad="10"/>
<connect gate="B" pin="I2" pad="12"/>
<connect gate="B" pin="I3" pad="13"/>
<connect gate="B" pin="O" pad="8"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="I0" pad="2"/>
<connect gate="A" pin="I1" pad="3"/>
<connect gate="A" pin="I2" pad="6"/>
<connect gate="A" pin="I3" pad="8"/>
<connect gate="A" pin="O" pad="9"/>
<connect gate="B" pin="I0" pad="13"/>
<connect gate="B" pin="I1" pad="14"/>
<connect gate="B" pin="I2" pad="18"/>
<connect gate="B" pin="I3" pad="19"/>
<connect gate="B" pin="O" pad="12"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="74*08" prefix="IC">
<description>Quad 2-input &lt;b&gt;AND&lt;/b&gt; gate</description>
<gates>
<gate name="A" symbol="7408" x="20.32" y="0" swaplevel="1"/>
<gate name="B" symbol="7408" x="20.32" y="-12.7" swaplevel="1"/>
<gate name="C" symbol="7408" x="43.18" y="0" swaplevel="1"/>
<gate name="D" symbol="7408" x="43.18" y="-12.7" swaplevel="1"/>
<gate name="P" symbol="PWRN" x="2.54" y="-7.62" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="O" pad="3"/>
<connect gate="B" pin="I0" pad="4"/>
<connect gate="B" pin="I1" pad="5"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I0" pad="9"/>
<connect gate="C" pin="I1" pad="10"/>
<connect gate="C" pin="O" pad="8"/>
<connect gate="D" pin="I0" pad="12"/>
<connect gate="D" pin="I1" pad="13"/>
<connect gate="D" pin="O" pad="11"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="D" package="SO14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="O" pad="3"/>
<connect gate="B" pin="I0" pad="4"/>
<connect gate="B" pin="I1" pad="5"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I0" pad="9"/>
<connect gate="C" pin="I1" pad="10"/>
<connect gate="C" pin="O" pad="8"/>
<connect gate="D" pin="I0" pad="12"/>
<connect gate="D" pin="I1" pad="13"/>
<connect gate="D" pin="O" pad="11"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="I0" pad="2"/>
<connect gate="A" pin="I1" pad="3"/>
<connect gate="A" pin="O" pad="4"/>
<connect gate="B" pin="I0" pad="6"/>
<connect gate="B" pin="I1" pad="8"/>
<connect gate="B" pin="O" pad="9"/>
<connect gate="C" pin="I0" pad="13"/>
<connect gate="C" pin="I1" pad="14"/>
<connect gate="C" pin="O" pad="12"/>
<connect gate="D" pin="I0" pad="18"/>
<connect gate="D" pin="I1" pad="19"/>
<connect gate="D" pin="O" pad="16"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="74*245" prefix="IC">
<description>Octal &lt;b&gt;BUS TRANSCEIVER&lt;/b&gt;, 3-state</description>
<gates>
<gate name="A" symbol="74245" x="20.32" y="0"/>
<gate name="P" symbol="PWRN" x="-5.08" y="0" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL20">
<connects>
<connect gate="A" pin="A1" pad="2"/>
<connect gate="A" pin="A2" pad="3"/>
<connect gate="A" pin="A3" pad="4"/>
<connect gate="A" pin="A4" pad="5"/>
<connect gate="A" pin="A5" pad="6"/>
<connect gate="A" pin="A6" pad="7"/>
<connect gate="A" pin="A7" pad="8"/>
<connect gate="A" pin="A8" pad="9"/>
<connect gate="A" pin="B1" pad="18"/>
<connect gate="A" pin="B2" pad="17"/>
<connect gate="A" pin="B3" pad="16"/>
<connect gate="A" pin="B4" pad="15"/>
<connect gate="A" pin="B5" pad="14"/>
<connect gate="A" pin="B6" pad="13"/>
<connect gate="A" pin="B7" pad="12"/>
<connect gate="A" pin="B8" pad="11"/>
<connect gate="A" pin="DIR" pad="1"/>
<connect gate="A" pin="G" pad="19"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
</technologies>
</device>
<device name="DW" package="SO20W">
<connects>
<connect gate="A" pin="A1" pad="2"/>
<connect gate="A" pin="A2" pad="3"/>
<connect gate="A" pin="A3" pad="4"/>
<connect gate="A" pin="A4" pad="5"/>
<connect gate="A" pin="A5" pad="6"/>
<connect gate="A" pin="A6" pad="7"/>
<connect gate="A" pin="A7" pad="8"/>
<connect gate="A" pin="A8" pad="9"/>
<connect gate="A" pin="B1" pad="18"/>
<connect gate="A" pin="B2" pad="17"/>
<connect gate="A" pin="B3" pad="16"/>
<connect gate="A" pin="B4" pad="15"/>
<connect gate="A" pin="B5" pad="14"/>
<connect gate="A" pin="B6" pad="13"/>
<connect gate="A" pin="B7" pad="12"/>
<connect gate="A" pin="B8" pad="11"/>
<connect gate="A" pin="DIR" pad="1"/>
<connect gate="A" pin="G" pad="19"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="A1" pad="2"/>
<connect gate="A" pin="A2" pad="3"/>
<connect gate="A" pin="A3" pad="4"/>
<connect gate="A" pin="A4" pad="5"/>
<connect gate="A" pin="A5" pad="6"/>
<connect gate="A" pin="A6" pad="7"/>
<connect gate="A" pin="A7" pad="8"/>
<connect gate="A" pin="A8" pad="9"/>
<connect gate="A" pin="B1" pad="18"/>
<connect gate="A" pin="B2" pad="17"/>
<connect gate="A" pin="B3" pad="16"/>
<connect gate="A" pin="B4" pad="15"/>
<connect gate="A" pin="B5" pad="14"/>
<connect gate="A" pin="B6" pad="13"/>
<connect gate="A" pin="B7" pad="12"/>
<connect gate="A" pin="B8" pad="11"/>
<connect gate="A" pin="DIR" pad="1"/>
<connect gate="A" pin="G" pad="19"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="74*32" prefix="IC">
<description>Quad 2-input &lt;b&gt;OR&lt;/b&gt; gate</description>
<gates>
<gate name="A" symbol="7432" x="15.24" y="5.08" swaplevel="1"/>
<gate name="B" symbol="7432" x="15.24" y="-10.16" swaplevel="1"/>
<gate name="C" symbol="7432" x="38.1" y="5.08" swaplevel="1"/>
<gate name="D" symbol="7432" x="38.1" y="-10.16" swaplevel="1"/>
<gate name="P" symbol="PWRN" x="-5.08" y="0" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="O" pad="3"/>
<connect gate="B" pin="I0" pad="4"/>
<connect gate="B" pin="I1" pad="5"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I0" pad="9"/>
<connect gate="C" pin="I1" pad="10"/>
<connect gate="C" pin="O" pad="8"/>
<connect gate="D" pin="I0" pad="12"/>
<connect gate="D" pin="I1" pad="13"/>
<connect gate="D" pin="O" pad="11"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="D" package="SO14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="O" pad="3"/>
<connect gate="B" pin="I0" pad="4"/>
<connect gate="B" pin="I1" pad="5"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I0" pad="9"/>
<connect gate="C" pin="I1" pad="10"/>
<connect gate="C" pin="O" pad="8"/>
<connect gate="D" pin="I0" pad="12"/>
<connect gate="D" pin="I1" pad="13"/>
<connect gate="D" pin="O" pad="11"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="I0" pad="2"/>
<connect gate="A" pin="I1" pad="3"/>
<connect gate="A" pin="O" pad="4"/>
<connect gate="B" pin="I0" pad="6"/>
<connect gate="B" pin="I1" pad="8"/>
<connect gate="B" pin="O" pad="9"/>
<connect gate="C" pin="I0" pad="13"/>
<connect gate="C" pin="I1" pad="14"/>
<connect gate="C" pin="O" pad="12"/>
<connect gate="D" pin="I0" pad="18"/>
<connect gate="D" pin="I1" pad="19"/>
<connect gate="D" pin="O" pad="16"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="74*157" prefix="IC">
<description>Quadruple 2-line to 1-line data &lt;b&gt;SELECTOR/MULTIPLEXER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="74157" x="20.32" y="0"/>
<gate name="P" symbol="PWRN" x="-5.08" y="0" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL16">
<connects>
<connect gate="A" pin="!A!/B" pad="1"/>
<connect gate="A" pin="1A" pad="2"/>
<connect gate="A" pin="1B" pad="3"/>
<connect gate="A" pin="1Y" pad="4"/>
<connect gate="A" pin="2A" pad="5"/>
<connect gate="A" pin="2B" pad="6"/>
<connect gate="A" pin="2Y" pad="7"/>
<connect gate="A" pin="3A" pad="11"/>
<connect gate="A" pin="3B" pad="10"/>
<connect gate="A" pin="3Y" pad="9"/>
<connect gate="A" pin="4A" pad="14"/>
<connect gate="A" pin="4B" pad="13"/>
<connect gate="A" pin="4Y" pad="12"/>
<connect gate="A" pin="G" pad="15"/>
<connect gate="P" pin="GND" pad="8"/>
<connect gate="P" pin="VCC" pad="16"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="D" package="SO16">
<connects>
<connect gate="A" pin="!A!/B" pad="1"/>
<connect gate="A" pin="1A" pad="2"/>
<connect gate="A" pin="1B" pad="3"/>
<connect gate="A" pin="1Y" pad="4"/>
<connect gate="A" pin="2A" pad="5"/>
<connect gate="A" pin="2B" pad="6"/>
<connect gate="A" pin="2Y" pad="7"/>
<connect gate="A" pin="3A" pad="11"/>
<connect gate="A" pin="3B" pad="10"/>
<connect gate="A" pin="3Y" pad="9"/>
<connect gate="A" pin="4A" pad="14"/>
<connect gate="A" pin="4B" pad="13"/>
<connect gate="A" pin="4Y" pad="12"/>
<connect gate="A" pin="G" pad="15"/>
<connect gate="P" pin="GND" pad="8"/>
<connect gate="P" pin="VCC" pad="16"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="!A!/B" pad="2"/>
<connect gate="A" pin="1A" pad="3"/>
<connect gate="A" pin="1B" pad="4"/>
<connect gate="A" pin="1Y" pad="5"/>
<connect gate="A" pin="2A" pad="7"/>
<connect gate="A" pin="2B" pad="8"/>
<connect gate="A" pin="2Y" pad="9"/>
<connect gate="A" pin="3A" pad="14"/>
<connect gate="A" pin="3B" pad="13"/>
<connect gate="A" pin="3Y" pad="12"/>
<connect gate="A" pin="4A" pad="18"/>
<connect gate="A" pin="4B" pad="17"/>
<connect gate="A" pin="4Y" pad="15"/>
<connect gate="A" pin="G" pad="19"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="74*04" prefix="IC">
<description>Hex &lt;b&gt;INVERTER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="7404" x="17.78" y="0" swaplevel="1"/>
<gate name="B" symbol="7404" x="17.78" y="-12.7" swaplevel="1"/>
<gate name="C" symbol="7404" x="17.78" y="-25.4" swaplevel="1"/>
<gate name="D" symbol="7404" x="45.72" y="0" swaplevel="1"/>
<gate name="E" symbol="7404" x="45.72" y="-12.7" swaplevel="1"/>
<gate name="F" symbol="7404" x="45.72" y="-25.4" swaplevel="1"/>
<gate name="P" symbol="PWRN" x="-5.08" y="-10.16" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL14">
<connects>
<connect gate="A" pin="I" pad="1"/>
<connect gate="A" pin="O" pad="2"/>
<connect gate="B" pin="I" pad="3"/>
<connect gate="B" pin="O" pad="4"/>
<connect gate="C" pin="I" pad="5"/>
<connect gate="C" pin="O" pad="6"/>
<connect gate="D" pin="I" pad="9"/>
<connect gate="D" pin="O" pad="8"/>
<connect gate="E" pin="I" pad="11"/>
<connect gate="E" pin="O" pad="10"/>
<connect gate="F" pin="I" pad="13"/>
<connect gate="F" pin="O" pad="12"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="D" package="SO14">
<connects>
<connect gate="A" pin="I" pad="1"/>
<connect gate="A" pin="O" pad="2"/>
<connect gate="B" pin="I" pad="3"/>
<connect gate="B" pin="O" pad="4"/>
<connect gate="C" pin="I" pad="5"/>
<connect gate="C" pin="O" pad="6"/>
<connect gate="D" pin="I" pad="9"/>
<connect gate="D" pin="O" pad="8"/>
<connect gate="E" pin="I" pad="11"/>
<connect gate="E" pin="O" pad="10"/>
<connect gate="F" pin="I" pad="13"/>
<connect gate="F" pin="O" pad="12"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="I" pad="2"/>
<connect gate="A" pin="O" pad="3"/>
<connect gate="B" pin="I" pad="4"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I" pad="8"/>
<connect gate="C" pin="O" pad="9"/>
<connect gate="D" pin="I" pad="13"/>
<connect gate="D" pin="O" pad="12"/>
<connect gate="E" pin="I" pad="16"/>
<connect gate="E" pin="O" pad="14"/>
<connect gate="F" pin="I" pad="19"/>
<connect gate="F" pin="O" pad="18"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="74*00" prefix="IC">
<description>Quad 2-input &lt;b&gt;NAND&lt;/b&gt; gate</description>
<gates>
<gate name="A" symbol="7400" x="20.32" y="0" swaplevel="1"/>
<gate name="B" symbol="7400" x="20.32" y="-12.7" swaplevel="1"/>
<gate name="C" symbol="7400" x="43.18" y="0" swaplevel="1"/>
<gate name="D" symbol="7400" x="43.18" y="-12.7" swaplevel="1"/>
<gate name="P" symbol="PWRN" x="5.08" y="-5.08" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="O" pad="3"/>
<connect gate="B" pin="I0" pad="4"/>
<connect gate="B" pin="I1" pad="5"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I0" pad="9"/>
<connect gate="C" pin="I1" pad="10"/>
<connect gate="C" pin="O" pad="8"/>
<connect gate="D" pin="I0" pad="12"/>
<connect gate="D" pin="I1" pad="13"/>
<connect gate="D" pin="O" pad="11"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="D" package="SO14">
<connects>
<connect gate="A" pin="I0" pad="1"/>
<connect gate="A" pin="I1" pad="2"/>
<connect gate="A" pin="O" pad="3"/>
<connect gate="B" pin="I0" pad="4"/>
<connect gate="B" pin="I1" pad="5"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I0" pad="9"/>
<connect gate="C" pin="I1" pad="10"/>
<connect gate="C" pin="O" pad="8"/>
<connect gate="D" pin="I0" pad="12"/>
<connect gate="D" pin="I1" pad="13"/>
<connect gate="D" pin="O" pad="11"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="I0" pad="2"/>
<connect gate="A" pin="I1" pad="3"/>
<connect gate="A" pin="O" pad="4"/>
<connect gate="B" pin="I0" pad="6"/>
<connect gate="B" pin="I1" pad="8"/>
<connect gate="B" pin="O" pad="9"/>
<connect gate="C" pin="I0" pad="13"/>
<connect gate="C" pin="I1" pad="14"/>
<connect gate="C" pin="O" pad="12"/>
<connect gate="D" pin="I0" pad="18"/>
<connect gate="D" pin="I1" pad="19"/>
<connect gate="D" pin="O" pad="16"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="74*02" prefix="IC">
<description>Quad 2-input &lt;b&gt;NOR&lt;/b&gt; gate</description>
<gates>
<gate name="A" symbol="7402" x="12.7" y="5.08" swaplevel="1"/>
<gate name="B" symbol="7402" x="12.7" y="-10.16" swaplevel="1"/>
<gate name="C" symbol="7402" x="35.56" y="5.08" swaplevel="1"/>
<gate name="D" symbol="7402" x="35.56" y="-10.16" swaplevel="1"/>
<gate name="P" symbol="PWRN" x="-5.08" y="0" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL14">
<connects>
<connect gate="A" pin="I0" pad="2"/>
<connect gate="A" pin="I1" pad="3"/>
<connect gate="A" pin="O" pad="1"/>
<connect gate="B" pin="I0" pad="5"/>
<connect gate="B" pin="I1" pad="6"/>
<connect gate="B" pin="O" pad="4"/>
<connect gate="C" pin="I0" pad="8"/>
<connect gate="C" pin="I1" pad="9"/>
<connect gate="C" pin="O" pad="10"/>
<connect gate="D" pin="I0" pad="11"/>
<connect gate="D" pin="I1" pad="12"/>
<connect gate="D" pin="O" pad="13"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="D" package="SO14">
<connects>
<connect gate="A" pin="I0" pad="2"/>
<connect gate="A" pin="I1" pad="3"/>
<connect gate="A" pin="O" pad="1"/>
<connect gate="B" pin="I0" pad="5"/>
<connect gate="B" pin="I1" pad="6"/>
<connect gate="B" pin="O" pad="4"/>
<connect gate="C" pin="I0" pad="8"/>
<connect gate="C" pin="I1" pad="9"/>
<connect gate="C" pin="O" pad="10"/>
<connect gate="D" pin="I0" pad="11"/>
<connect gate="D" pin="I1" pad="12"/>
<connect gate="D" pin="O" pad="13"/>
<connect gate="P" pin="GND" pad="7"/>
<connect gate="P" pin="VCC" pad="14"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="I0" pad="3"/>
<connect gate="A" pin="I1" pad="4"/>
<connect gate="A" pin="O" pad="2"/>
<connect gate="B" pin="I0" pad="8"/>
<connect gate="B" pin="I1" pad="9"/>
<connect gate="B" pin="O" pad="6"/>
<connect gate="C" pin="I0" pad="12"/>
<connect gate="C" pin="I1" pad="13"/>
<connect gate="C" pin="O" pad="14"/>
<connect gate="D" pin="I0" pad="16"/>
<connect gate="D" pin="I1" pad="18"/>
<connect gate="D" pin="O" pad="19"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name=""/>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="ALS"/>
<technology name="AS"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="74*374" prefix="IC">
<description>Octal D type transparent &lt;b&gt;LATCH&lt;/b&gt;, edge triggered</description>
<gates>
<gate name="A" symbol="74374" x="20.32" y="0"/>
<gate name="P" symbol="PWRN" x="-5.08" y="0" addlevel="request"/>
</gates>
<devices>
<device name="N" package="DIL20">
<connects>
<connect gate="A" pin="1D" pad="3"/>
<connect gate="A" pin="1Q" pad="2"/>
<connect gate="A" pin="2D" pad="4"/>
<connect gate="A" pin="2Q" pad="5"/>
<connect gate="A" pin="3D" pad="7"/>
<connect gate="A" pin="3Q" pad="6"/>
<connect gate="A" pin="4D" pad="8"/>
<connect gate="A" pin="4Q" pad="9"/>
<connect gate="A" pin="5D" pad="13"/>
<connect gate="A" pin="5Q" pad="12"/>
<connect gate="A" pin="6D" pad="14"/>
<connect gate="A" pin="6Q" pad="15"/>
<connect gate="A" pin="7D" pad="17"/>
<connect gate="A" pin="7Q" pad="16"/>
<connect gate="A" pin="8D" pad="18"/>
<connect gate="A" pin="8Q" pad="19"/>
<connect gate="A" pin="CLK" pad="11"/>
<connect gate="A" pin="OC" pad="1"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="DW" package="SO20W">
<connects>
<connect gate="A" pin="1D" pad="3"/>
<connect gate="A" pin="1Q" pad="2"/>
<connect gate="A" pin="2D" pad="4"/>
<connect gate="A" pin="2Q" pad="5"/>
<connect gate="A" pin="3D" pad="7"/>
<connect gate="A" pin="3Q" pad="6"/>
<connect gate="A" pin="4D" pad="8"/>
<connect gate="A" pin="4Q" pad="9"/>
<connect gate="A" pin="5D" pad="13"/>
<connect gate="A" pin="5Q" pad="12"/>
<connect gate="A" pin="6D" pad="14"/>
<connect gate="A" pin="6Q" pad="15"/>
<connect gate="A" pin="7D" pad="17"/>
<connect gate="A" pin="7Q" pad="16"/>
<connect gate="A" pin="8D" pad="18"/>
<connect gate="A" pin="8Q" pad="19"/>
<connect gate="A" pin="CLK" pad="11"/>
<connect gate="A" pin="OC" pad="1"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
<device name="FK" package="LCC20">
<connects>
<connect gate="A" pin="1D" pad="3"/>
<connect gate="A" pin="1Q" pad="2"/>
<connect gate="A" pin="2D" pad="4"/>
<connect gate="A" pin="2Q" pad="5"/>
<connect gate="A" pin="3D" pad="7"/>
<connect gate="A" pin="3Q" pad="6"/>
<connect gate="A" pin="4D" pad="8"/>
<connect gate="A" pin="4Q" pad="9"/>
<connect gate="A" pin="5D" pad="13"/>
<connect gate="A" pin="5Q" pad="12"/>
<connect gate="A" pin="6D" pad="14"/>
<connect gate="A" pin="6Q" pad="15"/>
<connect gate="A" pin="7D" pad="17"/>
<connect gate="A" pin="7Q" pad="16"/>
<connect gate="A" pin="8D" pad="18"/>
<connect gate="A" pin="8Q" pad="19"/>
<connect gate="A" pin="CLK" pad="11"/>
<connect gate="A" pin="OC" pad="1"/>
<connect gate="P" pin="GND" pad="10"/>
<connect gate="P" pin="VCC" pad="20"/>
</connects>
<technologies>
<technology name="AC"/>
<technology name="ACT"/>
<technology name="HC"/>
<technology name="HCT"/>
<technology name="LS"/>
<technology name="S"/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="frames" deviceset="DINA3_L" device=""/>
<part name="VCC1" library="pinhead" deviceset="PINHD-2X2" device=""/>
<part name="SUPPLY32" library="supply2" deviceset="+5V" device=""/>
<part name="JP1" library="pinhead" deviceset="PINHD-2X8" device=""/>
<part name="JP2" library="pinhead" deviceset="PINHD-2X8" device=""/>
<part name="SUPPLY35" library="supply2" deviceset="+5V" device=""/>
<part name="VCC2" library="pinhead" deviceset="PINHD-2X2" device=""/>
<part name="GND1" library="pinhead" deviceset="PINHD-2X2" device=""/>
<part name="GND2" library="pinhead" deviceset="PINHD-2X2" device=""/>
<part name="SUPPLY36" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY37" library="supply2" deviceset="GND" device=""/>
<part name="JP3" library="pinhead" deviceset="PINHD-2X8" device=""/>
<part name="JP4" library="pinhead" deviceset="PINHD-2X8" device=""/>
<part name="JP10" library="pinhead" deviceset="PINHD-2X18" device=""/>
<part name="FRAME2" library="frames" deviceset="DINA3_L" device=""/>
<part name="IC1" library="dawid" deviceset="MT5C6408" device=""/>
<part name="IC2" library="dawid" deviceset="MT5C6408" device=""/>
<part name="JP5" library="pinhead" deviceset="PINHD-2X5" device=""/>
<part name="IC3" library="74xx-eu" deviceset="74*27" device="N" technology="LS"/>
<part name="IC4" library="74xx-eu" deviceset="74*20" device="N" technology="LS"/>
<part name="IC5" library="74xx-eu" deviceset="74*08" device="N" technology="LS"/>
<part name="IC6" library="74xx-eu" deviceset="74*245" device="N" technology="LS"/>
<part name="IC7" library="74xx-eu" deviceset="74*245" device="N" technology="LS"/>
<part name="IC8" library="74xx-eu" deviceset="74*32" device="N" technology="LS"/>
<part name="IC9" library="74xx-eu" deviceset="74*157" device="N" technology="LS"/>
<part name="IC10" library="74xx-eu" deviceset="74*157" device="N" technology="LS"/>
<part name="IC11" library="74xx-eu" deviceset="74*157" device="N" technology="LS"/>
<part name="IC12" library="74xx-eu" deviceset="74*157" device="N" technology="LS"/>
<part name="SUPPLY1" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY2" library="supply2" deviceset="GND" device=""/>
<part name="IC13" library="74xx-eu" deviceset="74*157" device="N" technology="LS"/>
<part name="IC14" library="74xx-eu" deviceset="74*157" device="N" technology="LS"/>
<part name="SUPPLY5" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY3" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY4" library="supply2" deviceset="GND" device=""/>
<part name="IC15" library="74xx-eu" deviceset="74*04" device="N" technology="LS"/>
<part name="SUPPLY6" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY7" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY8" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY9" library="supply2" deviceset="+5V" device=""/>
<part name="SUPPLY10" library="supply2" deviceset="+5V" device=""/>
<part name="IC17" library="74xx-eu" deviceset="74*32" device="N" technology="LS"/>
<part name="IC18" library="74xx-eu" deviceset="74*00" device="N" technology="LS"/>
<part name="IC19" library="74xx-eu" deviceset="74*32" device="N" technology="LS"/>
<part name="IC20" library="74xx-eu" deviceset="74*02" device="N" technology="LS"/>
<part name="IC21" library="74xx-eu" deviceset="74*374" device="N" technology="LS"/>
<part name="SUPPLY11" library="supply2" deviceset="+5V" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="289.56" y="27.94" size="2.54" layer="97" font="vector">Memory Management Unit (MMU)</text>
<text x="386.08" y="33.02" size="2.54" layer="97" font="vector" rot="R180">Dawid Pilawa</text>
<text x="386.08" y="27.94" size="2.54" layer="97" font="vector" rot="R180">(C) 2010-2016</text>
<text x="370.84" y="10.16" size="2.54" layer="97" font="vector" rot="R180">CPU.0a</text>
<text x="386.08" y="10.16" size="2.54" layer="97" font="vector" rot="R180">2.0</text>
</plain>
<instances>
<instance part="FRAME1" gate="G$1" x="0" y="0"/>
<instance part="FRAME1" gate="G$2" x="287.02" y="0"/>
<instance part="IC1" gate="G$1" x="198.12" y="195.58"/>
<instance part="IC2" gate="G$1" x="198.12" y="73.66"/>
<instance part="IC1" gate="P" x="25.4" y="17.78"/>
<instance part="IC2" gate="P" x="38.1" y="17.78"/>
<instance part="IC3" gate="A" x="40.64" y="243.84"/>
<instance part="IC3" gate="B" x="40.64" y="231.14"/>
<instance part="IC3" gate="C" x="40.64" y="218.44"/>
<instance part="IC4" gate="A" x="66.04" y="210.82"/>
<instance part="IC5" gate="A" x="40.64" y="205.74"/>
<instance part="IC6" gate="A" x="254" y="203.2"/>
<instance part="IC7" gate="A" x="254" y="81.28"/>
<instance part="IC8" gate="A" x="93.98" y="172.72"/>
<instance part="IC9" gate="A" x="254" y="241.3"/>
<instance part="IC10" gate="A" x="254" y="165.1"/>
<instance part="IC11" gate="A" x="254" y="119.38"/>
<instance part="IC12" gate="A" x="353.06" y="81.28"/>
<instance part="SUPPLY1" gate="GND" x="238.76" y="147.32"/>
<instance part="SUPPLY2" gate="GND" x="182.88" y="167.64"/>
<instance part="IC13" gate="A" x="147.32" y="241.3"/>
<instance part="IC14" gate="A" x="147.32" y="203.2"/>
<instance part="SUPPLY5" gate="GND" x="182.88" y="45.72"/>
<instance part="IC8" gate="B" x="93.98" y="187.96"/>
<instance part="SUPPLY3" gate="GND" x="132.08" y="223.52"/>
<instance part="SUPPLY4" gate="GND" x="132.08" y="185.42"/>
<instance part="IC8" gate="C" x="93.98" y="157.48"/>
<instance part="IC8" gate="D" x="93.98" y="142.24"/>
<instance part="IC15" gate="A" x="71.12" y="154.94"/>
<instance part="SUPPLY6" gate="GND" x="238.76" y="223.52"/>
<instance part="SUPPLY7" gate="GND" x="238.76" y="101.6"/>
<instance part="SUPPLY8" gate="GND" x="337.82" y="63.5"/>
<instance part="SUPPLY9" gate="+5V" x="337.82" y="99.06"/>
<instance part="SUPPLY10" gate="+5V" x="236.22" y="137.16"/>
<instance part="IC17" gate="A" x="279.4" y="43.18"/>
<instance part="IC17" gate="B" x="279.4" y="55.88"/>
<instance part="IC5" gate="B" x="259.08" y="33.02"/>
<instance part="IC17" gate="C" x="322.58" y="88.9"/>
<instance part="IC18" gate="A" x="279.4" y="68.58"/>
<instance part="IC17" gate="D" x="233.68" y="58.42"/>
<instance part="IC19" gate="A" x="233.68" y="45.72"/>
<instance part="IC4" gate="B" x="93.98" y="104.14"/>
<instance part="IC21" gate="A" x="350.52" y="165.1"/>
<instance part="IC5" gate="C" x="322.58" y="68.58"/>
<instance part="SUPPLY11" gate="+5V" x="335.28" y="185.42"/>
<instance part="IC18" gate="C" x="307.34" y="129.54"/>
<instance part="IC19" gate="C" x="325.12" y="132.08"/>
<instance part="IC19" gate="D" x="320.04" y="154.94"/>
<instance part="IC15" gate="B" x="223.52" y="106.68" rot="R90"/>
<instance part="IC20" gate="B" x="40.64" y="88.9"/>
<instance part="IC5" gate="D" x="45.72" y="63.5"/>
</instances>
<busses>
<bus name="ABUS[0..15]">
<segment>
<wire x1="121.92" y1="259.08" x2="121.92" y2="213.36" width="0.762" layer="92"/>
<wire x1="121.92" y1="259.08" x2="119.38" y2="259.08" width="0.762" layer="92"/>
<label x="119.38" y="259.08" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<wire x1="17.78" y1="259.08" x2="20.32" y2="259.08" width="0.762" layer="92"/>
<label x="17.78" y="259.08" size="1.778" layer="95" rot="R180"/>
<wire x1="20.32" y1="259.08" x2="20.32" y2="78.74" width="0.762" layer="92"/>
</segment>
<segment>
<wire x1="317.5" y1="182.88" x2="320.04" y2="182.88" width="0.762" layer="92"/>
<wire x1="320.04" y1="182.88" x2="320.04" y2="172.72" width="0.762" layer="92"/>
</segment>
</bus>
<bus name="DBUS[0..7]">
<segment>
<wire x1="284.48" y1="220.98" x2="281.94" y2="220.98" width="0.762" layer="92"/>
<wire x1="281.94" y1="220.98" x2="281.94" y2="200.66" width="0.762" layer="92"/>
<label x="284.48" y="220.98" size="1.778" layer="95" rot="R270"/>
</segment>
<segment>
<wire x1="284.48" y1="99.06" x2="281.94" y2="99.06" width="0.762" layer="92"/>
<wire x1="281.94" y1="99.06" x2="281.94" y2="78.74" width="0.762" layer="92"/>
<label x="284.48" y="99.06" size="1.778" layer="95" rot="R270"/>
</segment>
<segment>
<wire x1="378.46" y1="182.88" x2="375.92" y2="182.88" width="0.762" layer="92"/>
<wire x1="375.92" y1="182.88" x2="375.92" y2="162.56" width="0.762" layer="92"/>
<label x="378.46" y="182.88" size="1.778" layer="95" rot="R270"/>
</segment>
</bus>
<bus name="PABUS[12..21]">
<segment>
<wire x1="284.48" y1="259.08" x2="281.94" y2="259.08" width="0.762" layer="92"/>
<wire x1="281.94" y1="259.08" x2="281.94" y2="241.3" width="0.762" layer="92"/>
<label x="284.48" y="259.08" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="284.48" y1="182.88" x2="281.94" y2="182.88" width="0.762" layer="92"/>
<wire x1="281.94" y1="182.88" x2="281.94" y2="165.1" width="0.762" layer="92"/>
<label x="284.48" y="182.88" size="1.778" layer="95" rot="R270"/>
</segment>
<segment>
<wire x1="284.48" y1="137.16" x2="281.94" y2="137.16" width="0.762" layer="92"/>
<wire x1="281.94" y1="137.16" x2="281.94" y2="129.54" width="0.762" layer="92"/>
<label x="284.48" y="137.16" size="1.778" layer="95" rot="R270"/>
</segment>
</bus>
</busses>
<nets>
<net name="ABUS8" class="0">
<segment>
<pinref part="IC3" gate="A" pin="I0"/>
<wire x1="20.32" y1="248.92" x2="22.86" y2="246.38" width="0.1524" layer="91"/>
<wire x1="22.86" y1="246.38" x2="33.02" y2="246.38" width="0.1524" layer="91"/>
<label x="22.86" y="246.38" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS9" class="0">
<segment>
<pinref part="IC3" gate="A" pin="I1"/>
<wire x1="20.32" y1="246.38" x2="22.86" y2="243.84" width="0.1524" layer="91"/>
<wire x1="22.86" y1="243.84" x2="33.02" y2="243.84" width="0.1524" layer="91"/>
<label x="22.86" y="243.84" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS10" class="0">
<segment>
<pinref part="IC3" gate="A" pin="I2"/>
<wire x1="20.32" y1="243.84" x2="22.86" y2="241.3" width="0.1524" layer="91"/>
<wire x1="22.86" y1="241.3" x2="33.02" y2="241.3" width="0.1524" layer="91"/>
<label x="22.86" y="241.3" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS11" class="0">
<segment>
<pinref part="IC3" gate="B" pin="I0"/>
<wire x1="20.32" y1="236.22" x2="22.86" y2="233.68" width="0.1524" layer="91"/>
<wire x1="22.86" y1="233.68" x2="33.02" y2="233.68" width="0.1524" layer="91"/>
<label x="22.86" y="233.68" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS12" class="0">
<segment>
<pinref part="IC3" gate="B" pin="I1"/>
<wire x1="20.32" y1="233.68" x2="22.86" y2="231.14" width="0.1524" layer="91"/>
<wire x1="22.86" y1="231.14" x2="33.02" y2="231.14" width="0.1524" layer="91"/>
<label x="22.86" y="231.14" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC13" gate="A" pin="1B"/>
<wire x1="121.92" y1="254" x2="124.46" y2="251.46" width="0.1524" layer="91"/>
<wire x1="124.46" y1="251.46" x2="134.62" y2="251.46" width="0.1524" layer="91"/>
<label x="124.46" y="251.46" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="1D"/>
<wire x1="320.04" y1="180.34" x2="322.58" y2="177.8" width="0.1524" layer="91"/>
<wire x1="322.58" y1="177.8" x2="337.82" y2="177.8" width="0.1524" layer="91"/>
<label x="322.58" y="177.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS13" class="0">
<segment>
<pinref part="IC3" gate="B" pin="I2"/>
<wire x1="20.32" y1="231.14" x2="22.86" y2="228.6" width="0.1524" layer="91"/>
<wire x1="22.86" y1="228.6" x2="33.02" y2="228.6" width="0.1524" layer="91"/>
<label x="22.86" y="228.6" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC13" gate="A" pin="2B"/>
<wire x1="121.92" y1="248.92" x2="124.46" y2="246.38" width="0.1524" layer="91"/>
<wire x1="124.46" y1="246.38" x2="134.62" y2="246.38" width="0.1524" layer="91"/>
<label x="124.46" y="246.38" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="2D"/>
<wire x1="320.04" y1="177.8" x2="322.58" y2="175.26" width="0.1524" layer="91"/>
<wire x1="322.58" y1="175.26" x2="337.82" y2="175.26" width="0.1524" layer="91"/>
<label x="322.58" y="175.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS14" class="0">
<segment>
<pinref part="IC3" gate="C" pin="I0"/>
<wire x1="20.32" y1="223.52" x2="22.86" y2="220.98" width="0.1524" layer="91"/>
<wire x1="22.86" y1="220.98" x2="33.02" y2="220.98" width="0.1524" layer="91"/>
<label x="22.86" y="220.98" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC13" gate="A" pin="3B"/>
<wire x1="121.92" y1="243.84" x2="124.46" y2="241.3" width="0.1524" layer="91"/>
<wire x1="124.46" y1="241.3" x2="134.62" y2="241.3" width="0.1524" layer="91"/>
<label x="124.46" y="241.3" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="3D"/>
<wire x1="320.04" y1="175.26" x2="322.58" y2="172.72" width="0.1524" layer="91"/>
<wire x1="322.58" y1="172.72" x2="337.82" y2="172.72" width="0.1524" layer="91"/>
<label x="322.58" y="172.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS15" class="0">
<segment>
<pinref part="IC3" gate="C" pin="I1"/>
<wire x1="20.32" y1="220.98" x2="22.86" y2="218.44" width="0.1524" layer="91"/>
<wire x1="22.86" y1="218.44" x2="33.02" y2="218.44" width="0.1524" layer="91"/>
<label x="22.86" y="218.44" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC13" gate="A" pin="4B"/>
<wire x1="121.92" y1="238.76" x2="124.46" y2="236.22" width="0.1524" layer="91"/>
<wire x1="124.46" y1="236.22" x2="134.62" y2="236.22" width="0.1524" layer="91"/>
<label x="124.46" y="236.22" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="4D"/>
<wire x1="320.04" y1="172.72" x2="322.58" y2="170.18" width="0.1524" layer="91"/>
<wire x1="322.58" y1="170.18" x2="337.82" y2="170.18" width="0.1524" layer="91"/>
<label x="322.58" y="170.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="/FS" class="0">
<segment>
<pinref part="IC3" gate="C" pin="I2"/>
<wire x1="33.02" y1="215.9" x2="15.24" y2="215.9" width="0.1524" layer="91"/>
<label x="15.24" y="215.9" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC14" gate="A" pin="2B"/>
<wire x1="134.62" y1="208.28" x2="129.54" y2="208.28" width="0.1524" layer="91"/>
<wire x1="129.54" y1="208.28" x2="129.54" y2="203.2" width="0.1524" layer="91"/>
<wire x1="129.54" y1="203.2" x2="114.3" y2="203.2" width="0.1524" layer="91"/>
<label x="114.3" y="203.2" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<wire x1="33.02" y1="86.36" x2="15.24" y2="86.36" width="0.1524" layer="91"/>
<label x="15.24" y="86.36" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="IC20" gate="B" pin="I1"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="6D"/>
<wire x1="337.82" y1="165.1" x2="317.5" y2="165.1" width="0.1524" layer="91"/>
<wire x1="317.5" y1="165.1" x2="317.5" y2="162.56" width="0.1524" layer="91"/>
<wire x1="317.5" y1="162.56" x2="309.88" y2="162.56" width="0.1524" layer="91"/>
<label x="309.88" y="162.56" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="IC4" gate="A" pin="I0"/>
<wire x1="58.42" y1="215.9" x2="55.88" y2="215.9" width="0.1524" layer="91"/>
<wire x1="55.88" y1="215.9" x2="55.88" y2="243.84" width="0.1524" layer="91"/>
<pinref part="IC3" gate="A" pin="O"/>
<wire x1="55.88" y1="243.84" x2="48.26" y2="243.84" width="0.1524" layer="91"/>
<junction x="55.88" y="215.9"/>
<wire x1="55.88" y1="215.9" x2="55.88" y2="109.22" width="0.1524" layer="91"/>
<pinref part="IC4" gate="B" pin="I0"/>
<wire x1="86.36" y1="109.22" x2="55.88" y2="109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="IC3" gate="B" pin="O"/>
<wire x1="48.26" y1="231.14" x2="53.34" y2="231.14" width="0.1524" layer="91"/>
<wire x1="53.34" y1="231.14" x2="53.34" y2="213.36" width="0.1524" layer="91"/>
<pinref part="IC4" gate="A" pin="I1"/>
<wire x1="53.34" y1="213.36" x2="58.42" y2="213.36" width="0.1524" layer="91"/>
<junction x="53.34" y="213.36"/>
<wire x1="53.34" y1="213.36" x2="53.34" y2="106.68" width="0.1524" layer="91"/>
<pinref part="IC4" gate="B" pin="I1"/>
<wire x1="86.36" y1="106.68" x2="53.34" y2="106.68" width="0.1524" layer="91"/>
</segment>
</net>
<net name="ABUS7" class="0">
<segment>
<pinref part="IC5" gate="A" pin="I0"/>
<wire x1="20.32" y1="210.82" x2="22.86" y2="208.28" width="0.1524" layer="91"/>
<wire x1="22.86" y1="208.28" x2="33.02" y2="208.28" width="0.1524" layer="91"/>
<label x="22.86" y="208.28" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="20.32" y1="93.98" x2="22.86" y2="91.44" width="0.1524" layer="91"/>
<wire x1="22.86" y1="91.44" x2="33.02" y2="91.44" width="0.1524" layer="91"/>
<label x="22.86" y="91.44" size="1.778" layer="95"/>
<pinref part="IC20" gate="B" pin="I0"/>
</segment>
</net>
<net name="MEMSEG" class="0">
<segment>
<pinref part="IC5" gate="A" pin="I1"/>
<wire x1="33.02" y1="203.2" x2="15.24" y2="203.2" width="0.1524" layer="91"/>
<label x="15.24" y="203.2" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC14" gate="A" pin="1B"/>
<wire x1="134.62" y1="213.36" x2="127" y2="213.36" width="0.1524" layer="91"/>
<wire x1="127" y1="213.36" x2="127" y2="208.28" width="0.1524" layer="91"/>
<wire x1="127" y1="208.28" x2="114.3" y2="208.28" width="0.1524" layer="91"/>
<label x="114.3" y="208.28" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<wire x1="33.02" y1="71.12" x2="15.24" y2="71.12" width="0.1524" layer="91"/>
<label x="15.24" y="71.12" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="5D"/>
<wire x1="337.82" y1="167.64" x2="309.88" y2="167.64" width="0.1524" layer="91"/>
<label x="309.88" y="167.64" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="IC5" gate="A" pin="O"/>
<wire x1="48.26" y1="205.74" x2="58.42" y2="205.74" width="0.1524" layer="91"/>
<pinref part="IC4" gate="A" pin="I3"/>
</segment>
</net>
<net name="/PTAB" class="0">
<segment>
<pinref part="IC8" gate="D" pin="I0"/>
<wire x1="83.82" y1="144.78" x2="86.36" y2="144.78" width="0.1524" layer="91"/>
<pinref part="IC8" gate="C" pin="I0"/>
<wire x1="83.82" y1="160.02" x2="86.36" y2="160.02" width="0.1524" layer="91"/>
<wire x1="83.82" y1="160.02" x2="83.82" y2="144.78" width="0.1524" layer="91"/>
<junction x="83.82" y="160.02"/>
<pinref part="IC8" gate="A" pin="I0"/>
<wire x1="83.82" y1="175.26" x2="86.36" y2="175.26" width="0.1524" layer="91"/>
<pinref part="IC14" gate="A" pin="!A!/B"/>
<wire x1="119.38" y1="193.04" x2="134.62" y2="193.04" width="0.1524" layer="91"/>
<pinref part="IC13" gate="A" pin="!A!/B"/>
<wire x1="119.38" y1="231.14" x2="134.62" y2="231.14" width="0.1524" layer="91"/>
<wire x1="119.38" y1="210.82" x2="119.38" y2="231.14" width="0.1524" layer="91"/>
<wire x1="119.38" y1="210.82" x2="119.38" y2="193.04" width="0.1524" layer="91"/>
<junction x="119.38" y="210.82"/>
<pinref part="IC4" gate="A" pin="O"/>
<wire x1="73.66" y1="210.82" x2="83.82" y2="210.82" width="0.1524" layer="91"/>
<wire x1="83.82" y1="210.82" x2="119.38" y2="210.82" width="0.1524" layer="91"/>
<junction x="83.82" y="210.82"/>
<wire x1="83.82" y1="210.82" x2="83.82" y2="190.5" width="0.1524" layer="91"/>
<pinref part="IC8" gate="B" pin="I0"/>
<wire x1="86.36" y1="190.5" x2="83.82" y2="190.5" width="0.1524" layer="91"/>
<junction x="83.82" y="190.5"/>
<wire x1="83.82" y1="190.5" x2="83.82" y2="175.26" width="0.1524" layer="91"/>
<wire x1="83.82" y1="175.26" x2="83.82" y2="160.02" width="0.1524" layer="91"/>
<junction x="83.82" y="175.26"/>
<label x="73.66" y="210.82" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC5" gate="C" pin="I0"/>
<wire x1="314.96" y1="71.12" x2="312.42" y2="71.12" width="0.1524" layer="91"/>
<label x="312.42" y="71.12" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/LDMEM" class="0">
<segment>
<pinref part="IC8" gate="A" pin="I1"/>
<wire x1="86.36" y1="170.18" x2="15.24" y2="170.18" width="0.1524" layer="91"/>
<label x="15.24" y="170.18" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC5" gate="B" pin="I0"/>
<wire x1="251.46" y1="35.56" x2="248.92" y2="35.56" width="0.1524" layer="91"/>
<label x="246.38" y="35.56" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="IC17" gate="B" pin="I1"/>
<wire x1="248.92" y1="35.56" x2="246.38" y2="35.56" width="0.1524" layer="91"/>
<wire x1="271.78" y1="53.34" x2="248.92" y2="53.34" width="0.1524" layer="91"/>
<wire x1="248.92" y1="53.34" x2="248.92" y2="35.56" width="0.1524" layer="91"/>
<junction x="248.92" y="35.56"/>
</segment>
<segment>
<pinref part="IC17" gate="C" pin="I0"/>
<wire x1="314.96" y1="91.44" x2="312.42" y2="91.44" width="0.1524" layer="91"/>
<label x="312.42" y="91.44" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="DQ1"/>
<pinref part="IC6" gate="A" pin="A1"/>
<wire x1="213.36" y1="215.9" x2="241.3" y2="215.9" width="0.1524" layer="91"/>
<wire x1="210.82" y1="215.9" x2="213.36" y2="215.9" width="0.1524" layer="91"/>
<wire x1="213.36" y1="215.9" x2="213.36" y2="254" width="0.1524" layer="91"/>
<pinref part="IC9" gate="A" pin="1A"/>
<wire x1="213.36" y1="254" x2="241.3" y2="254" width="0.1524" layer="91"/>
<junction x="213.36" y="215.9"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="DQ2"/>
<pinref part="IC6" gate="A" pin="A2"/>
<wire x1="210.82" y1="213.36" x2="215.9" y2="213.36" width="0.1524" layer="91"/>
<wire x1="215.9" y1="213.36" x2="241.3" y2="213.36" width="0.1524" layer="91"/>
<wire x1="215.9" y1="213.36" x2="215.9" y2="248.92" width="0.1524" layer="91"/>
<pinref part="IC9" gate="A" pin="2A"/>
<wire x1="215.9" y1="248.92" x2="241.3" y2="248.92" width="0.1524" layer="91"/>
<junction x="215.9" y="213.36"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="DQ3"/>
<pinref part="IC6" gate="A" pin="A3"/>
<wire x1="210.82" y1="210.82" x2="218.44" y2="210.82" width="0.1524" layer="91"/>
<wire x1="218.44" y1="210.82" x2="241.3" y2="210.82" width="0.1524" layer="91"/>
<wire x1="218.44" y1="210.82" x2="218.44" y2="243.84" width="0.1524" layer="91"/>
<pinref part="IC9" gate="A" pin="3A"/>
<wire x1="218.44" y1="243.84" x2="241.3" y2="243.84" width="0.1524" layer="91"/>
<junction x="218.44" y="210.82"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="DQ4"/>
<pinref part="IC6" gate="A" pin="A4"/>
<wire x1="210.82" y1="208.28" x2="220.98" y2="208.28" width="0.1524" layer="91"/>
<wire x1="220.98" y1="208.28" x2="241.3" y2="208.28" width="0.1524" layer="91"/>
<wire x1="220.98" y1="208.28" x2="220.98" y2="238.76" width="0.1524" layer="91"/>
<pinref part="IC9" gate="A" pin="4A"/>
<wire x1="220.98" y1="238.76" x2="241.3" y2="238.76" width="0.1524" layer="91"/>
<junction x="220.98" y="208.28"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="DQ5"/>
<pinref part="IC6" gate="A" pin="A5"/>
<wire x1="210.82" y1="205.74" x2="220.98" y2="205.74" width="0.1524" layer="91"/>
<wire x1="220.98" y1="205.74" x2="241.3" y2="205.74" width="0.1524" layer="91"/>
<wire x1="220.98" y1="205.74" x2="220.98" y2="177.8" width="0.1524" layer="91"/>
<pinref part="IC10" gate="A" pin="1A"/>
<wire x1="220.98" y1="177.8" x2="241.3" y2="177.8" width="0.1524" layer="91"/>
<junction x="220.98" y="205.74"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="DQ6"/>
<pinref part="IC6" gate="A" pin="A6"/>
<wire x1="210.82" y1="203.2" x2="218.44" y2="203.2" width="0.1524" layer="91"/>
<wire x1="218.44" y1="203.2" x2="241.3" y2="203.2" width="0.1524" layer="91"/>
<wire x1="218.44" y1="203.2" x2="218.44" y2="172.72" width="0.1524" layer="91"/>
<pinref part="IC10" gate="A" pin="2A"/>
<wire x1="218.44" y1="172.72" x2="241.3" y2="172.72" width="0.1524" layer="91"/>
<junction x="218.44" y="203.2"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="IC6" gate="A" pin="A7"/>
<wire x1="210.82" y1="200.66" x2="215.9" y2="200.66" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="DQ7"/>
<wire x1="215.9" y1="200.66" x2="241.3" y2="200.66" width="0.1524" layer="91"/>
<wire x1="215.9" y1="200.66" x2="215.9" y2="167.64" width="0.1524" layer="91"/>
<pinref part="IC10" gate="A" pin="3A"/>
<wire x1="215.9" y1="167.64" x2="241.3" y2="167.64" width="0.1524" layer="91"/>
<junction x="215.9" y="200.66"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="DQ8"/>
<pinref part="IC6" gate="A" pin="A8"/>
<wire x1="210.82" y1="198.12" x2="213.36" y2="198.12" width="0.1524" layer="91"/>
<pinref part="IC10" gate="A" pin="4A"/>
<wire x1="213.36" y1="198.12" x2="241.3" y2="198.12" width="0.1524" layer="91"/>
<wire x1="241.3" y1="162.56" x2="213.36" y2="162.56" width="0.1524" layer="91"/>
<wire x1="213.36" y1="162.56" x2="213.36" y2="198.12" width="0.1524" layer="91"/>
<junction x="213.36" y="198.12"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="IC9" gate="A" pin="4B"/>
<pinref part="IC9" gate="A" pin="3B"/>
<pinref part="IC9" gate="A" pin="2B"/>
<pinref part="IC9" gate="A" pin="1B"/>
<wire x1="238.76" y1="251.46" x2="241.3" y2="251.46" width="0.1524" layer="91"/>
<wire x1="238.76" y1="246.38" x2="238.76" y2="251.46" width="0.1524" layer="91"/>
<wire x1="238.76" y1="246.38" x2="241.3" y2="246.38" width="0.1524" layer="91"/>
<junction x="238.76" y="246.38"/>
<wire x1="238.76" y1="241.3" x2="238.76" y2="246.38" width="0.1524" layer="91"/>
<wire x1="238.76" y1="241.3" x2="241.3" y2="241.3" width="0.1524" layer="91"/>
<junction x="238.76" y="241.3"/>
<wire x1="238.76" y1="236.22" x2="238.76" y2="241.3" width="0.1524" layer="91"/>
<wire x1="238.76" y1="236.22" x2="241.3" y2="236.22" width="0.1524" layer="91"/>
<junction x="238.76" y="236.22"/>
<wire x1="238.76" y1="226.06" x2="238.76" y2="228.6" width="0.1524" layer="91"/>
<pinref part="SUPPLY6" gate="GND" pin="GND"/>
<pinref part="IC9" gate="A" pin="G"/>
<wire x1="238.76" y1="228.6" x2="238.76" y2="236.22" width="0.1524" layer="91"/>
<wire x1="241.3" y1="228.6" x2="238.76" y2="228.6" width="0.1524" layer="91"/>
<junction x="238.76" y="228.6"/>
</segment>
<segment>
<pinref part="SUPPLY1" gate="GND" pin="GND"/>
<wire x1="238.76" y1="149.86" x2="238.76" y2="152.4" width="0.1524" layer="91"/>
<wire x1="238.76" y1="152.4" x2="238.76" y2="160.02" width="0.1524" layer="91"/>
<wire x1="238.76" y1="160.02" x2="238.76" y2="165.1" width="0.1524" layer="91"/>
<wire x1="238.76" y1="165.1" x2="238.76" y2="170.18" width="0.1524" layer="91"/>
<wire x1="238.76" y1="170.18" x2="238.76" y2="175.26" width="0.1524" layer="91"/>
<pinref part="IC10" gate="A" pin="1B"/>
<wire x1="238.76" y1="175.26" x2="241.3" y2="175.26" width="0.1524" layer="91"/>
<pinref part="IC10" gate="A" pin="2B"/>
<wire x1="238.76" y1="170.18" x2="241.3" y2="170.18" width="0.1524" layer="91"/>
<pinref part="IC10" gate="A" pin="3B"/>
<wire x1="238.76" y1="165.1" x2="241.3" y2="165.1" width="0.1524" layer="91"/>
<pinref part="IC10" gate="A" pin="4B"/>
<wire x1="238.76" y1="160.02" x2="241.3" y2="160.02" width="0.1524" layer="91"/>
<junction x="238.76" y="160.02"/>
<junction x="238.76" y="165.1"/>
<junction x="238.76" y="170.18"/>
<junction x="238.76" y="152.4"/>
<pinref part="IC10" gate="A" pin="G"/>
<wire x1="238.76" y1="152.4" x2="241.3" y2="152.4" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="A6"/>
<pinref part="SUPPLY2" gate="GND" pin="GND"/>
<wire x1="185.42" y1="200.66" x2="182.88" y2="200.66" width="0.1524" layer="91"/>
<wire x1="182.88" y1="200.66" x2="182.88" y2="198.12" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A7"/>
<wire x1="182.88" y1="198.12" x2="182.88" y2="195.58" width="0.1524" layer="91"/>
<wire x1="182.88" y1="195.58" x2="182.88" y2="193.04" width="0.1524" layer="91"/>
<wire x1="182.88" y1="193.04" x2="182.88" y2="190.5" width="0.1524" layer="91"/>
<wire x1="182.88" y1="190.5" x2="182.88" y2="187.96" width="0.1524" layer="91"/>
<wire x1="182.88" y1="187.96" x2="182.88" y2="185.42" width="0.1524" layer="91"/>
<wire x1="182.88" y1="185.42" x2="182.88" y2="180.34" width="0.1524" layer="91"/>
<wire x1="182.88" y1="180.34" x2="182.88" y2="170.18" width="0.1524" layer="91"/>
<wire x1="182.88" y1="198.12" x2="185.42" y2="198.12" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A8"/>
<wire x1="182.88" y1="195.58" x2="185.42" y2="195.58" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A9"/>
<wire x1="182.88" y1="193.04" x2="185.42" y2="193.04" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A10"/>
<wire x1="182.88" y1="190.5" x2="185.42" y2="190.5" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A11"/>
<wire x1="182.88" y1="187.96" x2="185.42" y2="187.96" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A12"/>
<wire x1="182.88" y1="185.42" x2="185.42" y2="185.42" width="0.1524" layer="91"/>
<junction x="182.88" y="198.12"/>
<junction x="182.88" y="195.58"/>
<junction x="182.88" y="193.04"/>
<junction x="182.88" y="190.5"/>
<junction x="182.88" y="187.96"/>
<junction x="182.88" y="185.42"/>
<pinref part="IC1" gate="G$1" pin="!CE1"/>
<wire x1="185.42" y1="180.34" x2="182.88" y2="180.34" width="0.1524" layer="91"/>
<junction x="182.88" y="180.34"/>
</segment>
<segment>
<pinref part="SUPPLY5" gate="GND" pin="GND"/>
<wire x1="182.88" y1="48.26" x2="182.88" y2="58.42" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A6"/>
<wire x1="182.88" y1="58.42" x2="182.88" y2="63.5" width="0.1524" layer="91"/>
<wire x1="182.88" y1="63.5" x2="182.88" y2="66.04" width="0.1524" layer="91"/>
<wire x1="182.88" y1="66.04" x2="182.88" y2="68.58" width="0.1524" layer="91"/>
<wire x1="182.88" y1="68.58" x2="182.88" y2="71.12" width="0.1524" layer="91"/>
<wire x1="182.88" y1="71.12" x2="182.88" y2="73.66" width="0.1524" layer="91"/>
<wire x1="182.88" y1="73.66" x2="182.88" y2="76.2" width="0.1524" layer="91"/>
<wire x1="182.88" y1="76.2" x2="182.88" y2="78.74" width="0.1524" layer="91"/>
<wire x1="182.88" y1="78.74" x2="185.42" y2="78.74" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A7"/>
<wire x1="182.88" y1="76.2" x2="185.42" y2="76.2" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A8"/>
<wire x1="182.88" y1="73.66" x2="185.42" y2="73.66" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A9"/>
<wire x1="182.88" y1="71.12" x2="185.42" y2="71.12" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A10"/>
<wire x1="182.88" y1="68.58" x2="185.42" y2="68.58" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A11"/>
<wire x1="182.88" y1="66.04" x2="185.42" y2="66.04" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A12"/>
<wire x1="182.88" y1="63.5" x2="185.42" y2="63.5" width="0.1524" layer="91"/>
<junction x="182.88" y="76.2"/>
<junction x="182.88" y="73.66"/>
<junction x="182.88" y="71.12"/>
<junction x="182.88" y="68.58"/>
<junction x="182.88" y="66.04"/>
<junction x="182.88" y="63.5"/>
<junction x="182.88" y="58.42"/>
<pinref part="IC2" gate="G$1" pin="!CE1"/>
<wire x1="185.42" y1="58.42" x2="182.88" y2="58.42" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY3" gate="GND" pin="GND"/>
<wire x1="132.08" y1="226.06" x2="132.08" y2="228.6" width="0.1524" layer="91"/>
<pinref part="IC13" gate="A" pin="G"/>
<wire x1="132.08" y1="228.6" x2="134.62" y2="228.6" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY4" gate="GND" pin="GND"/>
<wire x1="132.08" y1="187.96" x2="132.08" y2="190.5" width="0.1524" layer="91"/>
<pinref part="IC14" gate="A" pin="G"/>
<wire x1="132.08" y1="190.5" x2="134.62" y2="190.5" width="0.1524" layer="91"/>
<wire x1="132.08" y1="190.5" x2="132.08" y2="198.12" width="0.1524" layer="91"/>
<pinref part="IC14" gate="A" pin="4B"/>
<wire x1="132.08" y1="198.12" x2="134.62" y2="198.12" width="0.1524" layer="91"/>
<junction x="132.08" y="190.5"/>
<wire x1="132.08" y1="198.12" x2="132.08" y2="203.2" width="0.1524" layer="91"/>
<pinref part="IC14" gate="A" pin="3A"/>
<wire x1="132.08" y1="203.2" x2="132.08" y2="205.74" width="0.1524" layer="91"/>
<wire x1="132.08" y1="205.74" x2="134.62" y2="205.74" width="0.1524" layer="91"/>
<pinref part="IC14" gate="A" pin="3B"/>
<wire x1="132.08" y1="203.2" x2="134.62" y2="203.2" width="0.1524" layer="91"/>
<junction x="132.08" y="203.2"/>
<junction x="132.08" y="198.12"/>
</segment>
<segment>
<pinref part="SUPPLY7" gate="GND" pin="GND"/>
<wire x1="238.76" y1="104.14" x2="238.76" y2="106.68" width="0.1524" layer="91"/>
<pinref part="IC11" gate="A" pin="G"/>
<wire x1="241.3" y1="106.68" x2="238.76" y2="106.68" width="0.1524" layer="91"/>
<wire x1="238.76" y1="106.68" x2="238.76" y2="114.3" width="0.1524" layer="91"/>
<pinref part="IC11" gate="A" pin="1B"/>
<wire x1="238.76" y1="114.3" x2="238.76" y2="116.84" width="0.1524" layer="91"/>
<wire x1="238.76" y1="116.84" x2="238.76" y2="124.46" width="0.1524" layer="91"/>
<wire x1="238.76" y1="124.46" x2="238.76" y2="129.54" width="0.1524" layer="91"/>
<wire x1="238.76" y1="129.54" x2="241.3" y2="129.54" width="0.1524" layer="91"/>
<pinref part="IC11" gate="A" pin="2B"/>
<wire x1="238.76" y1="124.46" x2="241.3" y2="124.46" width="0.1524" layer="91"/>
<junction x="238.76" y="124.46"/>
<junction x="238.76" y="106.68"/>
<pinref part="IC11" gate="A" pin="4B"/>
<wire x1="241.3" y1="114.3" x2="238.76" y2="114.3" width="0.1524" layer="91"/>
<pinref part="IC11" gate="A" pin="4A"/>
<wire x1="241.3" y1="116.84" x2="238.76" y2="116.84" width="0.1524" layer="91"/>
<junction x="238.76" y="116.84"/>
<junction x="238.76" y="114.3"/>
</segment>
<segment>
<pinref part="IC12" gate="A" pin="G"/>
<pinref part="SUPPLY8" gate="GND" pin="GND"/>
<wire x1="337.82" y1="66.04" x2="337.82" y2="68.58" width="0.1524" layer="91"/>
<wire x1="337.82" y1="68.58" x2="340.36" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="DQ1"/>
<pinref part="IC7" gate="A" pin="A1"/>
<wire x1="210.82" y1="93.98" x2="241.3" y2="93.98" width="0.1524" layer="91"/>
<wire x1="210.82" y1="93.98" x2="210.82" y2="132.08" width="0.1524" layer="91"/>
<pinref part="IC11" gate="A" pin="1A"/>
<wire x1="210.82" y1="132.08" x2="241.3" y2="132.08" width="0.1524" layer="91"/>
<junction x="210.82" y="93.98"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="DQ2"/>
<pinref part="IC7" gate="A" pin="A2"/>
<wire x1="210.82" y1="91.44" x2="213.36" y2="91.44" width="0.1524" layer="91"/>
<pinref part="IC11" gate="A" pin="2A"/>
<wire x1="213.36" y1="91.44" x2="241.3" y2="91.44" width="0.1524" layer="91"/>
<wire x1="241.3" y1="127" x2="213.36" y2="127" width="0.1524" layer="91"/>
<wire x1="213.36" y1="127" x2="213.36" y2="91.44" width="0.1524" layer="91"/>
<junction x="213.36" y="91.44"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="DQ3"/>
<pinref part="IC7" gate="A" pin="A3"/>
<wire x1="210.82" y1="88.9" x2="241.3" y2="88.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="DQ4"/>
<pinref part="IC7" gate="A" pin="A4"/>
<wire x1="210.82" y1="86.36" x2="241.3" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="DQ5"/>
<pinref part="IC7" gate="A" pin="A5"/>
<wire x1="210.82" y1="83.82" x2="241.3" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="FIO" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="DQ6"/>
<pinref part="IC7" gate="A" pin="A6"/>
<wire x1="210.82" y1="81.28" x2="223.52" y2="81.28" width="0.1524" layer="91"/>
<label x="210.82" y="81.28" size="1.4224" layer="95"/>
<wire x1="223.52" y1="81.28" x2="241.3" y2="81.28" width="0.1524" layer="91"/>
<wire x1="223.52" y1="96.52" x2="223.52" y2="81.28" width="0.1524" layer="91"/>
<junction x="223.52" y="81.28"/>
<pinref part="IC15" gate="B" pin="I"/>
</segment>
</net>
<net name="FWRITABLE" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="DQ7"/>
<pinref part="IC7" gate="A" pin="A7"/>
<label x="210.82" y="78.74" size="1.4224" layer="95"/>
<wire x1="210.82" y1="78.74" x2="223.52" y2="78.74" width="0.1524" layer="91"/>
<wire x1="223.52" y1="78.74" x2="241.3" y2="78.74" width="0.1524" layer="91"/>
<wire x1="223.52" y1="60.96" x2="223.52" y2="78.74" width="0.1524" layer="91"/>
<junction x="223.52" y="78.74"/>
<wire x1="223.52" y1="60.96" x2="226.06" y2="60.96" width="0.1524" layer="91"/>
<pinref part="IC17" gate="D" pin="I0"/>
</segment>
</net>
<net name="FPRESENT" class="0">
<segment>
<pinref part="IC2" gate="G$1" pin="DQ8"/>
<pinref part="IC7" gate="A" pin="A8"/>
<wire x1="210.82" y1="76.2" x2="213.36" y2="76.2" width="0.1524" layer="91"/>
<label x="210.82" y="76.2" size="1.4224" layer="95"/>
<wire x1="213.36" y1="76.2" x2="241.3" y2="76.2" width="0.1524" layer="91"/>
<wire x1="213.36" y1="48.26" x2="213.36" y2="76.2" width="0.1524" layer="91"/>
<junction x="213.36" y="76.2"/>
<wire x1="213.36" y1="48.26" x2="226.06" y2="48.26" width="0.1524" layer="91"/>
<pinref part="IC19" gate="A" pin="I0"/>
</segment>
</net>
<net name="/LDPTAB" class="0">
<segment>
<pinref part="IC8" gate="A" pin="O"/>
<wire x1="101.6" y1="172.72" x2="134.62" y2="172.72" width="0.1524" layer="91"/>
<label x="101.6" y="172.72" size="1.778" layer="95"/>
<pinref part="IC1" gate="G$1" pin="!WE"/>
<wire x1="134.62" y1="172.72" x2="185.42" y2="172.72" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="!WE"/>
<wire x1="134.62" y1="172.72" x2="134.62" y2="50.8" width="0.1524" layer="91"/>
<wire x1="134.62" y1="50.8" x2="185.42" y2="50.8" width="0.1524" layer="91"/>
<junction x="134.62" y="172.72"/>
</segment>
</net>
<net name="ABUS1" class="0">
<segment>
<pinref part="IC13" gate="A" pin="1A"/>
<wire x1="121.92" y1="256.54" x2="124.46" y2="254" width="0.1524" layer="91"/>
<wire x1="124.46" y1="254" x2="134.62" y2="254" width="0.1524" layer="91"/>
<label x="124.46" y="254" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS2" class="0">
<segment>
<pinref part="IC13" gate="A" pin="2A"/>
<wire x1="121.92" y1="251.46" x2="124.46" y2="248.92" width="0.1524" layer="91"/>
<wire x1="124.46" y1="248.92" x2="134.62" y2="248.92" width="0.1524" layer="91"/>
<label x="124.46" y="248.92" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS3" class="0">
<segment>
<pinref part="IC13" gate="A" pin="3A"/>
<wire x1="121.92" y1="246.38" x2="124.46" y2="243.84" width="0.1524" layer="91"/>
<wire x1="124.46" y1="243.84" x2="134.62" y2="243.84" width="0.1524" layer="91"/>
<label x="124.46" y="243.84" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS4" class="0">
<segment>
<pinref part="IC13" gate="A" pin="4A"/>
<wire x1="121.92" y1="241.3" x2="124.46" y2="238.76" width="0.1524" layer="91"/>
<wire x1="124.46" y1="238.76" x2="134.62" y2="238.76" width="0.1524" layer="91"/>
<label x="124.46" y="238.76" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="IC13" gate="A" pin="1Y"/>
<wire x1="160.02" y1="254" x2="180.34" y2="254" width="0.1524" layer="91"/>
<wire x1="180.34" y1="254" x2="180.34" y2="215.9" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A0"/>
<wire x1="180.34" y1="215.9" x2="185.42" y2="215.9" width="0.1524" layer="91"/>
<wire x1="180.34" y1="215.9" x2="180.34" y2="93.98" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A0"/>
<wire x1="180.34" y1="93.98" x2="185.42" y2="93.98" width="0.1524" layer="91"/>
<junction x="180.34" y="215.9"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="IC13" gate="A" pin="2Y"/>
<wire x1="160.02" y1="248.92" x2="177.8" y2="248.92" width="0.1524" layer="91"/>
<wire x1="177.8" y1="248.92" x2="177.8" y2="213.36" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A1"/>
<wire x1="177.8" y1="213.36" x2="185.42" y2="213.36" width="0.1524" layer="91"/>
<junction x="177.8" y="213.36"/>
<wire x1="177.8" y1="213.36" x2="177.8" y2="91.44" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A1"/>
<wire x1="177.8" y1="91.44" x2="185.42" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="IC13" gate="A" pin="3Y"/>
<wire x1="160.02" y1="243.84" x2="175.26" y2="243.84" width="0.1524" layer="91"/>
<wire x1="175.26" y1="243.84" x2="175.26" y2="210.82" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A2"/>
<wire x1="175.26" y1="210.82" x2="185.42" y2="210.82" width="0.1524" layer="91"/>
<junction x="175.26" y="210.82"/>
<pinref part="IC2" gate="G$1" pin="A2"/>
<wire x1="185.42" y1="88.9" x2="175.26" y2="88.9" width="0.1524" layer="91"/>
<wire x1="175.26" y1="88.9" x2="175.26" y2="210.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="IC13" gate="A" pin="4Y"/>
<wire x1="160.02" y1="238.76" x2="172.72" y2="238.76" width="0.1524" layer="91"/>
<wire x1="172.72" y1="238.76" x2="172.72" y2="208.28" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A3"/>
<wire x1="172.72" y1="208.28" x2="185.42" y2="208.28" width="0.1524" layer="91"/>
<junction x="172.72" y="208.28"/>
<wire x1="172.72" y1="208.28" x2="172.72" y2="86.36" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A3"/>
<wire x1="172.72" y1="86.36" x2="185.42" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="IC14" gate="A" pin="1Y"/>
<wire x1="160.02" y1="215.9" x2="170.18" y2="215.9" width="0.1524" layer="91"/>
<wire x1="170.18" y1="215.9" x2="170.18" y2="205.74" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A4"/>
<wire x1="170.18" y1="205.74" x2="185.42" y2="205.74" width="0.1524" layer="91"/>
<junction x="170.18" y="205.74"/>
<pinref part="IC2" gate="G$1" pin="A4"/>
<wire x1="185.42" y1="83.82" x2="170.18" y2="83.82" width="0.1524" layer="91"/>
<wire x1="170.18" y1="83.82" x2="170.18" y2="205.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<pinref part="IC14" gate="A" pin="2Y"/>
<wire x1="160.02" y1="210.82" x2="167.64" y2="210.82" width="0.1524" layer="91"/>
<wire x1="167.64" y1="210.82" x2="167.64" y2="203.2" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="A5"/>
<wire x1="167.64" y1="203.2" x2="185.42" y2="203.2" width="0.1524" layer="91"/>
<junction x="167.64" y="203.2"/>
<wire x1="167.64" y1="203.2" x2="167.64" y2="81.28" width="0.1524" layer="91"/>
<pinref part="IC2" gate="G$1" pin="A5"/>
<wire x1="167.64" y1="81.28" x2="185.42" y2="81.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="ABUS5" class="0">
<segment>
<pinref part="IC14" gate="A" pin="1A"/>
<wire x1="121.92" y1="218.44" x2="124.46" y2="215.9" width="0.1524" layer="91"/>
<wire x1="124.46" y1="215.9" x2="134.62" y2="215.9" width="0.1524" layer="91"/>
<label x="124.46" y="215.9" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="20.32" y1="78.74" x2="22.86" y2="76.2" width="0.1524" layer="91"/>
<wire x1="22.86" y1="76.2" x2="33.02" y2="76.2" width="0.1524" layer="91"/>
<label x="22.86" y="76.2" size="1.778" layer="95"/>
</segment>
</net>
<net name="ABUS6" class="0">
<segment>
<pinref part="IC14" gate="A" pin="2A"/>
<wire x1="121.92" y1="213.36" x2="124.46" y2="210.82" width="0.1524" layer="91"/>
<wire x1="124.46" y1="210.82" x2="134.62" y2="210.82" width="0.1524" layer="91"/>
<label x="124.46" y="210.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="/ENMEM" class="0">
<segment>
<pinref part="IC8" gate="B" pin="I1"/>
<wire x1="86.36" y1="185.42" x2="15.24" y2="185.42" width="0.1524" layer="91"/>
<label x="15.24" y="185.42" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC12" gate="A" pin="1B"/>
<wire x1="340.36" y1="91.44" x2="332.74" y2="91.44" width="0.1524" layer="91"/>
<wire x1="332.74" y1="91.44" x2="332.74" y2="96.52" width="0.1524" layer="91"/>
<wire x1="332.74" y1="96.52" x2="312.42" y2="96.52" width="0.1524" layer="91"/>
<label x="312.42" y="96.52" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC5" gate="B" pin="I1"/>
<wire x1="251.46" y1="30.48" x2="246.38" y2="30.48" width="0.1524" layer="91"/>
<label x="246.38" y="30.48" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC19" gate="D" pin="I0"/>
<wire x1="312.42" y1="157.48" x2="309.88" y2="157.48" width="0.1524" layer="91"/>
<label x="309.88" y="157.48" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/ENPTAB" class="0">
<segment>
<pinref part="IC8" gate="B" pin="O"/>
<wire x1="101.6" y1="187.96" x2="114.3" y2="187.96" width="0.1524" layer="91"/>
<wire x1="114.3" y1="187.96" x2="114.3" y2="200.66" width="0.1524" layer="91"/>
<pinref part="IC14" gate="A" pin="4A"/>
<wire x1="114.3" y1="200.66" x2="134.62" y2="200.66" width="0.1524" layer="91"/>
<label x="101.6" y="187.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC6" gate="A" pin="DIR"/>
<wire x1="241.3" y1="193.04" x2="238.76" y2="193.04" width="0.1524" layer="91"/>
<label x="238.76" y="193.04" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC7" gate="A" pin="DIR"/>
<wire x1="241.3" y1="71.12" x2="238.76" y2="71.12" width="0.1524" layer="91"/>
<label x="238.76" y="71.12" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="IC14" gate="A" pin="4Y"/>
<wire x1="160.02" y1="200.66" x2="162.56" y2="200.66" width="0.1524" layer="91"/>
<wire x1="162.56" y1="200.66" x2="162.56" y2="175.26" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="!OE"/>
<wire x1="162.56" y1="175.26" x2="185.42" y2="175.26" width="0.1524" layer="91"/>
<junction x="162.56" y="175.26"/>
<pinref part="IC2" gate="G$1" pin="!OE"/>
<wire x1="185.42" y1="53.34" x2="162.56" y2="53.34" width="0.1524" layer="91"/>
<wire x1="162.56" y1="53.34" x2="162.56" y2="175.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="IC8" gate="C" pin="O"/>
<wire x1="101.6" y1="157.48" x2="139.7" y2="157.48" width="0.1524" layer="91"/>
<wire x1="139.7" y1="157.48" x2="139.7" y2="177.8" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="CE2"/>
<wire x1="139.7" y1="177.8" x2="185.42" y2="177.8" width="0.1524" layer="91"/>
<wire x1="139.7" y1="157.48" x2="139.7" y2="40.64" width="0.1524" layer="91"/>
<wire x1="139.7" y1="40.64" x2="208.28" y2="40.64" width="0.1524" layer="91"/>
<wire x1="208.28" y1="40.64" x2="208.28" y2="68.58" width="0.1524" layer="91"/>
<pinref part="IC7" gate="A" pin="G"/>
<wire x1="208.28" y1="68.58" x2="241.3" y2="68.58" width="0.1524" layer="91"/>
<junction x="139.7" y="157.48"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="IC8" gate="D" pin="O"/>
<pinref part="IC2" gate="G$1" pin="CE2"/>
<wire x1="101.6" y1="142.24" x2="129.54" y2="142.24" width="0.1524" layer="91"/>
<wire x1="129.54" y1="142.24" x2="129.54" y2="55.88" width="0.1524" layer="91"/>
<wire x1="129.54" y1="55.88" x2="185.42" y2="55.88" width="0.1524" layer="91"/>
<wire x1="129.54" y1="142.24" x2="210.82" y2="142.24" width="0.1524" layer="91"/>
<wire x1="210.82" y1="142.24" x2="210.82" y2="190.5" width="0.1524" layer="91"/>
<pinref part="IC6" gate="A" pin="G"/>
<wire x1="210.82" y1="190.5" x2="241.3" y2="190.5" width="0.1524" layer="91"/>
<junction x="129.54" y="142.24"/>
</segment>
</net>
<net name="ABUS0" class="0">
<segment>
<pinref part="IC15" gate="A" pin="I"/>
<wire x1="20.32" y1="157.48" x2="22.86" y2="154.94" width="0.1524" layer="91"/>
<wire x1="22.86" y1="154.94" x2="58.42" y2="154.94" width="0.1524" layer="91"/>
<label x="22.86" y="154.94" size="1.778" layer="95"/>
<pinref part="IC8" gate="D" pin="I1"/>
<wire x1="58.42" y1="154.94" x2="60.96" y2="154.94" width="0.1524" layer="91"/>
<wire x1="86.36" y1="139.7" x2="58.42" y2="139.7" width="0.1524" layer="91"/>
<wire x1="58.42" y1="139.7" x2="58.42" y2="154.94" width="0.1524" layer="91"/>
<junction x="58.42" y="154.94"/>
</segment>
</net>
<net name="N$30" class="0">
<segment>
<pinref part="IC15" gate="A" pin="O"/>
<pinref part="IC8" gate="C" pin="I1"/>
<wire x1="81.28" y1="154.94" x2="86.36" y2="154.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="DBUS0" class="0">
<segment>
<pinref part="IC6" gate="A" pin="B1"/>
<wire x1="281.94" y1="218.44" x2="279.4" y2="215.9" width="0.1524" layer="91"/>
<wire x1="266.7" y1="215.9" x2="279.4" y2="215.9" width="0.1524" layer="91"/>
<label x="266.7" y="215.9" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC7" gate="A" pin="B1"/>
<wire x1="281.94" y1="96.52" x2="279.4" y2="93.98" width="0.1524" layer="91"/>
<wire x1="279.4" y1="93.98" x2="266.7" y2="93.98" width="0.1524" layer="91"/>
<label x="266.7" y="93.98" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="1Q"/>
<wire x1="375.92" y1="180.34" x2="373.38" y2="177.8" width="0.1524" layer="91"/>
<wire x1="373.38" y1="177.8" x2="363.22" y2="177.8" width="0.1524" layer="91"/>
<label x="363.22" y="177.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="DBUS1" class="0">
<segment>
<pinref part="IC6" gate="A" pin="B2"/>
<wire x1="281.94" y1="215.9" x2="279.4" y2="213.36" width="0.1524" layer="91"/>
<wire x1="279.4" y1="213.36" x2="266.7" y2="213.36" width="0.1524" layer="91"/>
<label x="266.7" y="213.36" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC7" gate="A" pin="B2"/>
<wire x1="281.94" y1="93.98" x2="279.4" y2="91.44" width="0.1524" layer="91"/>
<wire x1="279.4" y1="91.44" x2="266.7" y2="91.44" width="0.1524" layer="91"/>
<label x="266.7" y="91.44" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="2Q"/>
<wire x1="375.92" y1="177.8" x2="373.38" y2="175.26" width="0.1524" layer="91"/>
<wire x1="373.38" y1="175.26" x2="363.22" y2="175.26" width="0.1524" layer="91"/>
<label x="363.22" y="175.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="DBUS2" class="0">
<segment>
<pinref part="IC6" gate="A" pin="B3"/>
<wire x1="281.94" y1="213.36" x2="279.4" y2="210.82" width="0.1524" layer="91"/>
<wire x1="279.4" y1="210.82" x2="266.7" y2="210.82" width="0.1524" layer="91"/>
<label x="266.7" y="210.82" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC7" gate="A" pin="B3"/>
<wire x1="281.94" y1="91.44" x2="279.4" y2="88.9" width="0.1524" layer="91"/>
<wire x1="279.4" y1="88.9" x2="266.7" y2="88.9" width="0.1524" layer="91"/>
<label x="266.7" y="88.9" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="3Q"/>
<wire x1="375.92" y1="175.26" x2="373.38" y2="172.72" width="0.1524" layer="91"/>
<wire x1="373.38" y1="172.72" x2="363.22" y2="172.72" width="0.1524" layer="91"/>
<label x="363.22" y="172.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="DBUS3" class="0">
<segment>
<pinref part="IC6" gate="A" pin="B4"/>
<wire x1="281.94" y1="210.82" x2="279.4" y2="208.28" width="0.1524" layer="91"/>
<wire x1="279.4" y1="208.28" x2="266.7" y2="208.28" width="0.1524" layer="91"/>
<label x="266.7" y="208.28" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC7" gate="A" pin="B4"/>
<wire x1="281.94" y1="88.9" x2="279.4" y2="86.36" width="0.1524" layer="91"/>
<wire x1="279.4" y1="86.36" x2="266.7" y2="86.36" width="0.1524" layer="91"/>
<label x="266.7" y="86.36" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="4Q"/>
<wire x1="375.92" y1="172.72" x2="373.38" y2="170.18" width="0.1524" layer="91"/>
<wire x1="373.38" y1="170.18" x2="363.22" y2="170.18" width="0.1524" layer="91"/>
<label x="363.22" y="170.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="DBUS4" class="0">
<segment>
<pinref part="IC6" gate="A" pin="B5"/>
<wire x1="281.94" y1="208.28" x2="279.4" y2="205.74" width="0.1524" layer="91"/>
<wire x1="279.4" y1="205.74" x2="266.7" y2="205.74" width="0.1524" layer="91"/>
<label x="266.7" y="205.74" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC7" gate="A" pin="B5"/>
<wire x1="281.94" y1="86.36" x2="279.4" y2="83.82" width="0.1524" layer="91"/>
<wire x1="279.4" y1="83.82" x2="266.7" y2="83.82" width="0.1524" layer="91"/>
<label x="266.7" y="83.82" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="5Q"/>
<wire x1="375.92" y1="170.18" x2="373.38" y2="167.64" width="0.1524" layer="91"/>
<wire x1="373.38" y1="167.64" x2="363.22" y2="167.64" width="0.1524" layer="91"/>
<label x="363.22" y="167.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="DBUS5" class="0">
<segment>
<pinref part="IC6" gate="A" pin="B6"/>
<wire x1="281.94" y1="205.74" x2="279.4" y2="203.2" width="0.1524" layer="91"/>
<wire x1="279.4" y1="203.2" x2="266.7" y2="203.2" width="0.1524" layer="91"/>
<label x="266.7" y="203.2" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC7" gate="A" pin="B6"/>
<wire x1="281.94" y1="83.82" x2="279.4" y2="81.28" width="0.1524" layer="91"/>
<wire x1="279.4" y1="81.28" x2="266.7" y2="81.28" width="0.1524" layer="91"/>
<label x="266.7" y="81.28" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="6Q"/>
<wire x1="375.92" y1="167.64" x2="373.38" y2="165.1" width="0.1524" layer="91"/>
<wire x1="373.38" y1="165.1" x2="363.22" y2="165.1" width="0.1524" layer="91"/>
<label x="363.22" y="165.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="DBUS6" class="0">
<segment>
<pinref part="IC6" gate="A" pin="B7"/>
<wire x1="281.94" y1="203.2" x2="279.4" y2="200.66" width="0.1524" layer="91"/>
<wire x1="279.4" y1="200.66" x2="266.7" y2="200.66" width="0.1524" layer="91"/>
<label x="266.7" y="200.66" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC7" gate="A" pin="B7"/>
<wire x1="281.94" y1="81.28" x2="279.4" y2="78.74" width="0.1524" layer="91"/>
<wire x1="279.4" y1="78.74" x2="266.7" y2="78.74" width="0.1524" layer="91"/>
<label x="266.7" y="78.74" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="7Q"/>
<wire x1="375.92" y1="165.1" x2="373.38" y2="162.56" width="0.1524" layer="91"/>
<wire x1="373.38" y1="162.56" x2="363.22" y2="162.56" width="0.1524" layer="91"/>
<label x="363.22" y="162.56" size="1.778" layer="95"/>
</segment>
</net>
<net name="DBUS7" class="0">
<segment>
<pinref part="IC6" gate="A" pin="B8"/>
<wire x1="281.94" y1="200.66" x2="279.4" y2="198.12" width="0.1524" layer="91"/>
<wire x1="279.4" y1="198.12" x2="266.7" y2="198.12" width="0.1524" layer="91"/>
<label x="266.7" y="198.12" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC7" gate="A" pin="B8"/>
<wire x1="281.94" y1="78.74" x2="279.4" y2="76.2" width="0.1524" layer="91"/>
<wire x1="279.4" y1="76.2" x2="266.7" y2="76.2" width="0.1524" layer="91"/>
<label x="266.7" y="76.2" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="8Q"/>
<wire x1="375.92" y1="162.56" x2="373.38" y2="160.02" width="0.1524" layer="91"/>
<wire x1="373.38" y1="160.02" x2="363.22" y2="160.02" width="0.1524" layer="91"/>
<label x="363.22" y="160.02" size="1.778" layer="95"/>
</segment>
</net>
<net name="/FP" class="0">
<segment>
<pinref part="IC9" gate="A" pin="!A!/B"/>
<wire x1="241.3" y1="231.14" x2="236.22" y2="231.14" width="0.1524" layer="91"/>
<label x="236.22" y="231.14" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC10" gate="A" pin="!A!/B"/>
<wire x1="241.3" y1="154.94" x2="236.22" y2="154.94" width="0.1524" layer="91"/>
<label x="236.22" y="154.94" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC11" gate="A" pin="!A!/B"/>
<wire x1="241.3" y1="109.22" x2="236.22" y2="109.22" width="0.1524" layer="91"/>
<label x="236.22" y="109.22" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC17" gate="D" pin="I1"/>
<wire x1="226.06" y1="55.88" x2="223.52" y2="55.88" width="0.1524" layer="91"/>
<label x="220.98" y="55.88" size="1.778" layer="95" rot="R180" xref="yes"/>
<pinref part="IC19" gate="A" pin="I1"/>
<wire x1="223.52" y1="55.88" x2="220.98" y2="55.88" width="0.1524" layer="91"/>
<wire x1="226.06" y1="43.18" x2="223.52" y2="43.18" width="0.1524" layer="91"/>
<wire x1="223.52" y1="43.18" x2="223.52" y2="55.88" width="0.1524" layer="91"/>
<junction x="223.52" y="55.88"/>
</segment>
</net>
<net name="PABUS12" class="0">
<segment>
<pinref part="IC9" gate="A" pin="1Y"/>
<wire x1="281.94" y1="256.54" x2="279.4" y2="254" width="0.1524" layer="91"/>
<wire x1="279.4" y1="254" x2="266.7" y2="254" width="0.1524" layer="91"/>
<label x="266.7" y="254" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS13" class="0">
<segment>
<pinref part="IC9" gate="A" pin="2Y"/>
<wire x1="281.94" y1="251.46" x2="279.4" y2="248.92" width="0.1524" layer="91"/>
<wire x1="279.4" y1="248.92" x2="266.7" y2="248.92" width="0.1524" layer="91"/>
<label x="266.7" y="248.92" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS14" class="0">
<segment>
<pinref part="IC9" gate="A" pin="3Y"/>
<wire x1="281.94" y1="246.38" x2="279.4" y2="243.84" width="0.1524" layer="91"/>
<wire x1="279.4" y1="243.84" x2="266.7" y2="243.84" width="0.1524" layer="91"/>
<label x="266.7" y="243.84" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS15" class="0">
<segment>
<pinref part="IC9" gate="A" pin="4Y"/>
<wire x1="281.94" y1="241.3" x2="279.4" y2="238.76" width="0.1524" layer="91"/>
<wire x1="279.4" y1="238.76" x2="266.7" y2="238.76" width="0.1524" layer="91"/>
<label x="266.7" y="238.76" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS16" class="0">
<segment>
<pinref part="IC10" gate="A" pin="1Y"/>
<wire x1="281.94" y1="180.34" x2="279.4" y2="177.8" width="0.1524" layer="91"/>
<wire x1="279.4" y1="177.8" x2="266.7" y2="177.8" width="0.1524" layer="91"/>
<label x="266.7" y="177.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS17" class="0">
<segment>
<pinref part="IC10" gate="A" pin="2Y"/>
<wire x1="281.94" y1="175.26" x2="279.4" y2="172.72" width="0.1524" layer="91"/>
<wire x1="279.4" y1="172.72" x2="266.7" y2="172.72" width="0.1524" layer="91"/>
<label x="266.7" y="172.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS18" class="0">
<segment>
<pinref part="IC10" gate="A" pin="3Y"/>
<wire x1="281.94" y1="170.18" x2="279.4" y2="167.64" width="0.1524" layer="91"/>
<wire x1="279.4" y1="167.64" x2="266.7" y2="167.64" width="0.1524" layer="91"/>
<label x="266.7" y="167.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS19" class="0">
<segment>
<pinref part="IC10" gate="A" pin="4Y"/>
<wire x1="281.94" y1="165.1" x2="279.4" y2="162.56" width="0.1524" layer="91"/>
<wire x1="279.4" y1="162.56" x2="266.7" y2="162.56" width="0.1524" layer="91"/>
<label x="266.7" y="162.56" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS20" class="0">
<segment>
<pinref part="IC11" gate="A" pin="1Y"/>
<wire x1="281.94" y1="134.62" x2="279.4" y2="132.08" width="0.1524" layer="91"/>
<wire x1="279.4" y1="132.08" x2="266.7" y2="132.08" width="0.1524" layer="91"/>
<label x="266.7" y="132.08" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS21" class="0">
<segment>
<pinref part="IC11" gate="A" pin="2Y"/>
<wire x1="281.94" y1="129.54" x2="279.4" y2="127" width="0.1524" layer="91"/>
<wire x1="279.4" y1="127" x2="266.7" y2="127" width="0.1524" layer="91"/>
<label x="266.7" y="127" size="1.778" layer="95"/>
</segment>
</net>
<net name="/IO" class="0">
<segment>
<pinref part="IC11" gate="A" pin="3Y"/>
<wire x1="266.7" y1="121.92" x2="271.78" y2="121.92" width="0.1524" layer="91"/>
<label x="276.86" y="121.92" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="SUPPLY9" gate="+5V" pin="+5V"/>
<pinref part="IC12" gate="A" pin="2A"/>
<wire x1="337.82" y1="96.52" x2="337.82" y2="93.98" width="0.1524" layer="91"/>
<wire x1="337.82" y1="93.98" x2="337.82" y2="88.9" width="0.1524" layer="91"/>
<wire x1="337.82" y1="88.9" x2="337.82" y2="83.82" width="0.1524" layer="91"/>
<wire x1="337.82" y1="83.82" x2="337.82" y2="78.74" width="0.1524" layer="91"/>
<wire x1="340.36" y1="88.9" x2="337.82" y2="88.9" width="0.1524" layer="91"/>
<pinref part="IC12" gate="A" pin="3A"/>
<wire x1="340.36" y1="83.82" x2="337.82" y2="83.82" width="0.1524" layer="91"/>
<pinref part="IC12" gate="A" pin="4A"/>
<wire x1="340.36" y1="78.74" x2="337.82" y2="78.74" width="0.1524" layer="91"/>
<junction x="337.82" y="83.82"/>
<junction x="337.82" y="88.9"/>
<pinref part="IC12" gate="A" pin="1A"/>
<wire x1="340.36" y1="93.98" x2="337.82" y2="93.98" width="0.1524" layer="91"/>
<junction x="337.82" y="93.98"/>
</segment>
<segment>
<pinref part="IC11" gate="A" pin="3B"/>
<wire x1="241.3" y1="119.38" x2="236.22" y2="119.38" width="0.1524" layer="91"/>
<pinref part="SUPPLY10" gate="+5V" pin="+5V"/>
<wire x1="236.22" y1="119.38" x2="236.22" y2="134.62" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC21" gate="A" pin="8D"/>
<wire x1="337.82" y1="160.02" x2="335.28" y2="160.02" width="0.1524" layer="91"/>
<pinref part="SUPPLY11" gate="+5V" pin="+5V"/>
<wire x1="335.28" y1="160.02" x2="335.28" y2="162.56" width="0.1524" layer="91"/>
<pinref part="IC21" gate="A" pin="7D"/>
<wire x1="335.28" y1="162.56" x2="335.28" y2="182.88" width="0.1524" layer="91"/>
<wire x1="337.82" y1="162.56" x2="335.28" y2="162.56" width="0.1524" layer="91"/>
<junction x="335.28" y="162.56"/>
</segment>
</net>
<net name="/ENMEMX" class="0">
<segment>
<pinref part="IC12" gate="A" pin="1Y"/>
<wire x1="365.76" y1="93.98" x2="368.3" y2="93.98" width="0.1524" layer="91"/>
<label x="383.54" y="93.98" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/LDMEMX" class="0">
<segment>
<pinref part="IC12" gate="A" pin="2Y"/>
<wire x1="365.76" y1="88.9" x2="368.3" y2="88.9" width="0.1524" layer="91"/>
<label x="383.54" y="88.9" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/WR_FAULT" class="0">
<segment>
<pinref part="IC12" gate="A" pin="3Y"/>
<wire x1="365.76" y1="83.82" x2="368.3" y2="83.82" width="0.1524" layer="91"/>
<label x="386.08" y="83.82" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/NP_FAULT" class="0">
<segment>
<pinref part="IC12" gate="A" pin="4Y"/>
<wire x1="365.76" y1="78.74" x2="368.3" y2="78.74" width="0.1524" layer="91"/>
<label x="386.08" y="78.74" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<wire x1="223.52" y1="116.84" x2="223.52" y2="121.92" width="0.1524" layer="91"/>
<pinref part="IC11" gate="A" pin="3A"/>
<wire x1="223.52" y1="121.92" x2="241.3" y2="121.92" width="0.1524" layer="91"/>
<pinref part="IC15" gate="B" pin="O"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="IC12" gate="A" pin="2B"/>
<wire x1="335.28" y1="86.36" x2="340.36" y2="86.36" width="0.1524" layer="91"/>
<pinref part="IC17" gate="C" pin="O"/>
<wire x1="330.2" y1="88.9" x2="335.28" y2="88.9" width="0.1524" layer="91"/>
<wire x1="335.28" y1="88.9" x2="335.28" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="IC17" gate="B" pin="O"/>
<wire x1="287.02" y1="55.88" x2="294.64" y2="55.88" width="0.1524" layer="91"/>
<pinref part="IC12" gate="A" pin="3B"/>
<wire x1="294.64" y1="55.88" x2="294.64" y2="81.28" width="0.1524" layer="91"/>
<wire x1="294.64" y1="81.28" x2="340.36" y2="81.28" width="0.1524" layer="91"/>
<wire x1="294.64" y1="81.28" x2="294.64" y2="132.08" width="0.1524" layer="91"/>
<junction x="294.64" y="81.28"/>
<wire x1="294.64" y1="132.08" x2="299.72" y2="132.08" width="0.1524" layer="91"/>
<pinref part="IC18" gate="C" pin="I0"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="IC17" gate="A" pin="O"/>
<wire x1="287.02" y1="43.18" x2="297.18" y2="43.18" width="0.1524" layer="91"/>
<wire x1="297.18" y1="43.18" x2="297.18" y2="76.2" width="0.1524" layer="91"/>
<pinref part="IC12" gate="A" pin="4B"/>
<wire x1="297.18" y1="76.2" x2="340.36" y2="76.2" width="0.1524" layer="91"/>
<wire x1="297.18" y1="76.2" x2="297.18" y2="127" width="0.1524" layer="91"/>
<junction x="297.18" y="76.2"/>
<wire x1="297.18" y1="127" x2="299.72" y2="127" width="0.1524" layer="91"/>
<pinref part="IC18" gate="C" pin="I1"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="IC5" gate="B" pin="O"/>
<wire x1="266.7" y1="33.02" x2="269.24" y2="33.02" width="0.1524" layer="91"/>
<wire x1="269.24" y1="33.02" x2="269.24" y2="40.64" width="0.1524" layer="91"/>
<pinref part="IC17" gate="A" pin="I1"/>
<wire x1="269.24" y1="40.64" x2="271.78" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="IC18" gate="A" pin="O"/>
<wire x1="287.02" y1="68.58" x2="292.1" y2="68.58" width="0.1524" layer="91"/>
<wire x1="292.1" y1="68.58" x2="292.1" y2="86.36" width="0.1524" layer="91"/>
<pinref part="IC17" gate="C" pin="I1"/>
<wire x1="292.1" y1="86.36" x2="314.96" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="IC18" gate="A" pin="I1"/>
<wire x1="269.24" y1="66.04" x2="271.78" y2="66.04" width="0.1524" layer="91"/>
<pinref part="IC17" gate="B" pin="I0"/>
<wire x1="269.24" y1="58.42" x2="269.24" y2="66.04" width="0.1524" layer="91"/>
<pinref part="IC17" gate="D" pin="O"/>
<wire x1="241.3" y1="58.42" x2="269.24" y2="58.42" width="0.1524" layer="91"/>
<junction x="269.24" y="58.42"/>
<wire x1="269.24" y1="58.42" x2="271.78" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<pinref part="IC18" gate="A" pin="I0"/>
<wire x1="264.16" y1="71.12" x2="271.78" y2="71.12" width="0.1524" layer="91"/>
<pinref part="IC17" gate="A" pin="I0"/>
<wire x1="264.16" y1="45.72" x2="271.78" y2="45.72" width="0.1524" layer="91"/>
<wire x1="264.16" y1="45.72" x2="264.16" y2="71.12" width="0.1524" layer="91"/>
<pinref part="IC19" gate="A" pin="O"/>
<wire x1="241.3" y1="45.72" x2="264.16" y2="45.72" width="0.1524" layer="91"/>
<junction x="264.16" y="45.72"/>
</segment>
</net>
<net name="/PPREG" class="0">
<segment>
<pinref part="IC4" gate="B" pin="O"/>
<wire x1="101.6" y1="104.14" x2="104.14" y2="104.14" width="0.1524" layer="91"/>
<label x="116.84" y="104.14" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC5" gate="C" pin="I1"/>
<wire x1="314.96" y1="66.04" x2="312.42" y2="66.04" width="0.1524" layer="91"/>
<label x="312.42" y="66.04" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="IC19" gate="D" pin="I1"/>
<wire x1="309.88" y1="152.4" x2="312.42" y2="152.4" width="0.1524" layer="91"/>
<label x="309.88" y="152.4" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="IC5" gate="C" pin="O"/>
<wire x1="330.2" y1="68.58" x2="335.28" y2="68.58" width="0.1524" layer="91"/>
<wire x1="335.28" y1="68.58" x2="335.28" y2="71.12" width="0.1524" layer="91"/>
<pinref part="IC12" gate="A" pin="!A!/B"/>
<wire x1="335.28" y1="71.12" x2="340.36" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="IC18" gate="C" pin="O"/>
<pinref part="IC19" gate="C" pin="I1"/>
<wire x1="314.96" y1="129.54" x2="317.5" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="CLK0A" class="0">
<segment>
<pinref part="IC19" gate="C" pin="I0"/>
<wire x1="317.5" y1="134.62" x2="314.96" y2="134.62" width="0.1524" layer="91"/>
<wire x1="314.96" y1="134.62" x2="314.96" y2="137.16" width="0.1524" layer="91"/>
<wire x1="314.96" y1="137.16" x2="304.8" y2="137.16" width="0.1524" layer="91"/>
<label x="304.8" y="137.16" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<pinref part="IC21" gate="A" pin="CLK"/>
<wire x1="337.82" y1="152.4" x2="335.28" y2="152.4" width="0.1524" layer="91"/>
<wire x1="335.28" y1="152.4" x2="335.28" y2="132.08" width="0.1524" layer="91"/>
<pinref part="IC19" gate="C" pin="O"/>
<wire x1="335.28" y1="132.08" x2="332.74" y2="132.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$42" class="0">
<segment>
<pinref part="IC19" gate="D" pin="O"/>
<wire x1="327.66" y1="154.94" x2="337.82" y2="154.94" width="0.1524" layer="91"/>
<pinref part="IC21" gate="A" pin="OC"/>
</segment>
</net>
<net name="N$37" class="0">
<segment>
<pinref part="IC4" gate="B" pin="I2"/>
<pinref part="IC3" gate="C" pin="O"/>
<wire x1="48.26" y1="218.44" x2="50.8" y2="218.44" width="0.1524" layer="91"/>
<wire x1="50.8" y1="218.44" x2="50.8" y2="208.28" width="0.1524" layer="91"/>
<pinref part="IC4" gate="A" pin="I2"/>
<wire x1="50.8" y1="208.28" x2="58.42" y2="208.28" width="0.1524" layer="91"/>
<junction x="50.8" y="208.28"/>
<wire x1="50.8" y1="208.28" x2="50.8" y2="101.6" width="0.1524" layer="91"/>
<wire x1="86.36" y1="101.6" x2="50.8" y2="101.6" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
<sheet>
<plain>
<text x="289.56" y="27.94" size="2.54" layer="97" font="vector">Memory Management Unit (MMU)</text>
<text x="386.08" y="33.02" size="2.54" layer="97" font="vector" rot="R180">Dawid Pilawa</text>
<text x="386.08" y="27.94" size="2.54" layer="97" font="vector" rot="R180">(C) 2010-2014</text>
<text x="370.84" y="10.16" size="2.54" layer="97" font="vector" rot="R180">CPU.0a</text>
<text x="386.08" y="10.16" size="2.54" layer="97" font="vector" rot="R180">2.0</text>
<text x="10.16" y="246.38" size="6.4516" layer="91">BOARD CONNECTORS</text>
</plain>
<instances>
<instance part="FRAME2" gate="G$1" x="0" y="0"/>
<instance part="FRAME2" gate="G$2" x="287.02" y="0"/>
<instance part="VCC1" gate="A" x="22.86" y="226.06"/>
<instance part="SUPPLY32" gate="+5V" x="10.16" y="233.68"/>
<instance part="JP1" gate="A" x="86.36" y="226.06"/>
<instance part="JP2" gate="A" x="86.36" y="187.96"/>
<instance part="SUPPLY35" gate="+5V" x="33.02" y="233.68"/>
<instance part="VCC2" gate="A" x="22.86" y="213.36"/>
<instance part="GND1" gate="A" x="22.86" y="195.58"/>
<instance part="GND2" gate="A" x="22.86" y="182.88"/>
<instance part="SUPPLY36" gate="GND" x="10.16" y="175.26"/>
<instance part="SUPPLY37" gate="GND" x="33.02" y="175.26"/>
<instance part="JP3" gate="A" x="154.94" y="226.06"/>
<instance part="JP4" gate="A" x="154.94" y="187.96"/>
<instance part="JP10" gate="A" x="86.36" y="132.08"/>
<instance part="JP5" gate="A" x="154.94" y="147.32"/>
</instances>
<busses>
<bus name="DBUS[0..7]">
<segment>
<wire x1="63.5" y1="238.76" x2="66.04" y2="238.76" width="0.762" layer="92"/>
<wire x1="66.04" y1="238.76" x2="66.04" y2="218.44" width="0.762" layer="92"/>
<label x="63.5" y="238.76" size="1.778" layer="95" rot="R180"/>
</segment>
</bus>
<bus name="ALUBUS[0..15]">
<segment>
<wire x1="129.54" y1="238.76" x2="132.08" y2="238.76" width="0.762" layer="92"/>
<wire x1="132.08" y1="238.76" x2="132.08" y2="210.82" width="0.762" layer="92"/>
<wire x1="132.08" y1="210.82" x2="180.34" y2="210.82" width="0.762" layer="92"/>
<wire x1="180.34" y1="210.82" x2="180.34" y2="236.22" width="0.762" layer="92"/>
<label x="129.54" y="238.76" size="1.778" layer="95" rot="R180"/>
</segment>
</bus>
<bus name="RBUS[0..15]">
<segment>
<wire x1="129.54" y1="200.66" x2="132.08" y2="200.66" width="0.762" layer="92"/>
<wire x1="132.08" y1="200.66" x2="132.08" y2="172.72" width="0.762" layer="92"/>
<wire x1="132.08" y1="172.72" x2="180.34" y2="172.72" width="0.762" layer="92"/>
<wire x1="180.34" y1="172.72" x2="180.34" y2="198.12" width="0.762" layer="92"/>
</segment>
</bus>
<bus name="IRQ[0..7]">
<segment>
<wire x1="106.68" y1="238.76" x2="109.22" y2="238.76" width="0.762" layer="92"/>
<wire x1="109.22" y1="238.76" x2="109.22" y2="218.44" width="0.762" layer="92"/>
<label x="106.68" y="238.76" size="1.778" layer="95" rot="R180"/>
</segment>
</bus>
<bus name="ABUS[0..15]">
<segment>
<wire x1="63.5" y1="200.66" x2="66.04" y2="200.66" width="0.762" layer="92"/>
<wire x1="66.04" y1="200.66" x2="66.04" y2="172.72" width="0.762" layer="92"/>
<wire x1="66.04" y1="172.72" x2="109.22" y2="172.72" width="0.762" layer="92"/>
<wire x1="109.22" y1="172.72" x2="109.22" y2="198.12" width="0.762" layer="92"/>
<label x="63.5" y="200.66" size="1.778" layer="95" rot="R180"/>
</segment>
</bus>
<bus name="PABUS[12..21]">
<segment>
<wire x1="129.54" y1="157.48" x2="132.08" y2="157.48" width="0.762" layer="92"/>
<wire x1="132.08" y1="157.48" x2="132.08" y2="132.08" width="0.762" layer="92"/>
<wire x1="132.08" y1="132.08" x2="180.34" y2="132.08" width="0.762" layer="92"/>
<wire x1="180.34" y1="132.08" x2="180.34" y2="154.94" width="0.762" layer="92"/>
<label x="114.3" y="154.94" size="1.778" layer="95"/>
</segment>
</bus>
</busses>
<nets>
<net name="/ALUHI2MEM" class="0">
<segment>
<wire x1="83.82" y1="121.92" x2="73.66" y2="121.92" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="25"/>
<label x="73.66" y="121.92" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/ALULO2MEM" class="0">
<segment>
<wire x1="83.82" y1="116.84" x2="73.66" y2="116.84" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="29"/>
<label x="73.66" y="116.84" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/MEM2ALUHI" class="0">
<segment>
<wire x1="83.82" y1="119.38" x2="73.66" y2="119.38" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="27"/>
<label x="73.66" y="119.38" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/MEM2ALULO" class="0">
<segment>
<wire x1="83.82" y1="114.3" x2="73.66" y2="114.3" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="31"/>
<label x="73.66" y="114.3" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="DBUS0" class="0">
<segment>
<wire x1="66.04" y1="236.22" x2="68.58" y2="233.68" width="0.1524" layer="91"/>
<wire x1="68.58" y1="233.68" x2="83.82" y2="233.68" width="0.1524" layer="91"/>
<label x="68.58" y="233.68" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="1"/>
</segment>
</net>
<net name="DBUS1" class="0">
<segment>
<wire x1="66.04" y1="233.68" x2="68.58" y2="231.14" width="0.1524" layer="91"/>
<wire x1="68.58" y1="231.14" x2="83.82" y2="231.14" width="0.1524" layer="91"/>
<label x="68.58" y="231.14" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="3"/>
</segment>
</net>
<net name="DBUS2" class="0">
<segment>
<wire x1="66.04" y1="231.14" x2="68.58" y2="228.6" width="0.1524" layer="91"/>
<wire x1="68.58" y1="228.6" x2="83.82" y2="228.6" width="0.1524" layer="91"/>
<label x="68.58" y="228.6" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="5"/>
</segment>
</net>
<net name="DBUS3" class="0">
<segment>
<wire x1="66.04" y1="228.6" x2="68.58" y2="226.06" width="0.1524" layer="91"/>
<wire x1="68.58" y1="226.06" x2="83.82" y2="226.06" width="0.1524" layer="91"/>
<label x="68.58" y="226.06" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="7"/>
</segment>
</net>
<net name="DBUS4" class="0">
<segment>
<wire x1="66.04" y1="226.06" x2="68.58" y2="223.52" width="0.1524" layer="91"/>
<wire x1="68.58" y1="223.52" x2="83.82" y2="223.52" width="0.1524" layer="91"/>
<label x="68.58" y="223.52" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="9"/>
</segment>
</net>
<net name="DBUS5" class="0">
<segment>
<wire x1="66.04" y1="223.52" x2="68.58" y2="220.98" width="0.1524" layer="91"/>
<wire x1="68.58" y1="220.98" x2="83.82" y2="220.98" width="0.1524" layer="91"/>
<label x="68.58" y="220.98" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="11"/>
</segment>
</net>
<net name="DBUS6" class="0">
<segment>
<wire x1="66.04" y1="220.98" x2="68.58" y2="218.44" width="0.1524" layer="91"/>
<wire x1="68.58" y1="218.44" x2="83.82" y2="218.44" width="0.1524" layer="91"/>
<label x="68.58" y="218.44" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="13"/>
</segment>
</net>
<net name="DBUS7" class="0">
<segment>
<wire x1="66.04" y1="218.44" x2="68.58" y2="215.9" width="0.1524" layer="91"/>
<wire x1="68.58" y1="215.9" x2="83.82" y2="215.9" width="0.1524" layer="91"/>
<label x="68.58" y="215.9" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="15"/>
</segment>
</net>
<net name="ALUBUS8" class="0">
<segment>
<pinref part="JP3" gate="A" pin="9"/>
<wire x1="132.08" y1="226.06" x2="134.62" y2="223.52" width="0.1524" layer="91"/>
<wire x1="134.62" y1="223.52" x2="152.4" y2="223.52" width="0.1524" layer="91"/>
<label x="134.62" y="223.52" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS9" class="0">
<segment>
<pinref part="JP3" gate="A" pin="10"/>
<wire x1="180.34" y1="226.06" x2="177.8" y2="223.52" width="0.1524" layer="91"/>
<wire x1="177.8" y1="223.52" x2="160.02" y2="223.52" width="0.1524" layer="91"/>
<label x="165.1" y="223.52" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS10" class="0">
<segment>
<pinref part="JP3" gate="A" pin="11"/>
<wire x1="132.08" y1="223.52" x2="134.62" y2="220.98" width="0.1524" layer="91"/>
<wire x1="134.62" y1="220.98" x2="152.4" y2="220.98" width="0.1524" layer="91"/>
<label x="134.62" y="220.98" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS11" class="0">
<segment>
<pinref part="JP3" gate="A" pin="12"/>
<wire x1="180.34" y1="223.52" x2="177.8" y2="220.98" width="0.1524" layer="91"/>
<wire x1="177.8" y1="220.98" x2="160.02" y2="220.98" width="0.1524" layer="91"/>
<label x="165.1" y="220.98" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS12" class="0">
<segment>
<pinref part="JP3" gate="A" pin="13"/>
<wire x1="132.08" y1="220.98" x2="134.62" y2="218.44" width="0.1524" layer="91"/>
<wire x1="134.62" y1="218.44" x2="152.4" y2="218.44" width="0.1524" layer="91"/>
<label x="134.62" y="218.44" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS13" class="0">
<segment>
<pinref part="JP3" gate="A" pin="14"/>
<wire x1="180.34" y1="220.98" x2="177.8" y2="218.44" width="0.1524" layer="91"/>
<wire x1="177.8" y1="218.44" x2="160.02" y2="218.44" width="0.1524" layer="91"/>
<label x="165.1" y="218.44" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS15" class="0">
<segment>
<pinref part="JP3" gate="A" pin="16"/>
<wire x1="180.34" y1="218.44" x2="177.8" y2="215.9" width="0.1524" layer="91"/>
<wire x1="177.8" y1="215.9" x2="160.02" y2="215.9" width="0.1524" layer="91"/>
<label x="165.1" y="215.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS14" class="0">
<segment>
<pinref part="JP3" gate="A" pin="15"/>
<wire x1="132.08" y1="218.44" x2="134.62" y2="215.9" width="0.1524" layer="91"/>
<wire x1="134.62" y1="215.9" x2="152.4" y2="215.9" width="0.1524" layer="91"/>
<label x="134.62" y="215.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS0" class="0">
<segment>
<pinref part="JP3" gate="A" pin="1"/>
<wire x1="132.08" y1="236.22" x2="134.62" y2="233.68" width="0.1524" layer="91"/>
<wire x1="134.62" y1="233.68" x2="152.4" y2="233.68" width="0.1524" layer="91"/>
<label x="134.62" y="233.68" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS1" class="0">
<segment>
<pinref part="JP3" gate="A" pin="2"/>
<wire x1="180.34" y1="236.22" x2="177.8" y2="233.68" width="0.1524" layer="91"/>
<wire x1="177.8" y1="233.68" x2="160.02" y2="233.68" width="0.1524" layer="91"/>
<label x="165.1" y="233.68" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS2" class="0">
<segment>
<pinref part="JP3" gate="A" pin="3"/>
<wire x1="132.08" y1="233.68" x2="134.62" y2="231.14" width="0.1524" layer="91"/>
<wire x1="134.62" y1="231.14" x2="152.4" y2="231.14" width="0.1524" layer="91"/>
<label x="134.62" y="231.14" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS3" class="0">
<segment>
<pinref part="JP3" gate="A" pin="4"/>
<wire x1="180.34" y1="233.68" x2="177.8" y2="231.14" width="0.1524" layer="91"/>
<wire x1="177.8" y1="231.14" x2="160.02" y2="231.14" width="0.1524" layer="91"/>
<label x="165.1" y="231.14" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS4" class="0">
<segment>
<pinref part="JP3" gate="A" pin="5"/>
<wire x1="132.08" y1="231.14" x2="134.62" y2="228.6" width="0.1524" layer="91"/>
<wire x1="134.62" y1="228.6" x2="152.4" y2="228.6" width="0.1524" layer="91"/>
<label x="134.62" y="228.6" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS5" class="0">
<segment>
<pinref part="JP3" gate="A" pin="6"/>
<wire x1="180.34" y1="231.14" x2="177.8" y2="228.6" width="0.1524" layer="91"/>
<wire x1="177.8" y1="228.6" x2="160.02" y2="228.6" width="0.1524" layer="91"/>
<label x="165.1" y="228.6" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS6" class="0">
<segment>
<pinref part="JP3" gate="A" pin="7"/>
<wire x1="132.08" y1="228.6" x2="134.62" y2="226.06" width="0.1524" layer="91"/>
<wire x1="134.62" y1="226.06" x2="152.4" y2="226.06" width="0.1524" layer="91"/>
<label x="134.62" y="226.06" size="1.778" layer="95"/>
</segment>
</net>
<net name="ALUBUS7" class="0">
<segment>
<pinref part="JP3" gate="A" pin="8"/>
<wire x1="180.34" y1="228.6" x2="177.8" y2="226.06" width="0.1524" layer="91"/>
<wire x1="177.8" y1="226.06" x2="160.02" y2="226.06" width="0.1524" layer="91"/>
<label x="165.1" y="226.06" size="1.778" layer="95"/>
</segment>
</net>
<net name="/ENABUS" class="0">
<segment>
<wire x1="91.44" y1="127" x2="101.6" y2="127" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="22"/>
<label x="101.6" y="127" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="ABUS0" class="0">
<segment>
<wire x1="66.04" y1="198.12" x2="68.58" y2="195.58" width="0.1524" layer="91"/>
<wire x1="68.58" y1="195.58" x2="83.82" y2="195.58" width="0.1524" layer="91"/>
<label x="68.58" y="195.58" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="1"/>
</segment>
</net>
<net name="ABUS1" class="0">
<segment>
<wire x1="109.22" y1="198.12" x2="106.68" y2="195.58" width="0.1524" layer="91"/>
<wire x1="106.68" y1="195.58" x2="91.44" y2="195.58" width="0.1524" layer="91"/>
<label x="99.06" y="195.58" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="2"/>
</segment>
</net>
<net name="ABUS2" class="0">
<segment>
<wire x1="66.04" y1="195.58" x2="68.58" y2="193.04" width="0.1524" layer="91"/>
<wire x1="68.58" y1="193.04" x2="83.82" y2="193.04" width="0.1524" layer="91"/>
<label x="68.58" y="193.04" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="3"/>
</segment>
</net>
<net name="ABUS3" class="0">
<segment>
<wire x1="109.22" y1="195.58" x2="106.68" y2="193.04" width="0.1524" layer="91"/>
<wire x1="106.68" y1="193.04" x2="91.44" y2="193.04" width="0.1524" layer="91"/>
<label x="99.06" y="193.04" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="4"/>
</segment>
</net>
<net name="ABUS4" class="0">
<segment>
<wire x1="66.04" y1="193.04" x2="68.58" y2="190.5" width="0.1524" layer="91"/>
<wire x1="68.58" y1="190.5" x2="83.82" y2="190.5" width="0.1524" layer="91"/>
<label x="68.58" y="190.5" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="5"/>
</segment>
</net>
<net name="ABUS5" class="0">
<segment>
<wire x1="109.22" y1="193.04" x2="106.68" y2="190.5" width="0.1524" layer="91"/>
<wire x1="106.68" y1="190.5" x2="91.44" y2="190.5" width="0.1524" layer="91"/>
<label x="99.06" y="190.5" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="6"/>
</segment>
</net>
<net name="ABUS6" class="0">
<segment>
<wire x1="66.04" y1="190.5" x2="68.58" y2="187.96" width="0.1524" layer="91"/>
<wire x1="68.58" y1="187.96" x2="83.82" y2="187.96" width="0.1524" layer="91"/>
<label x="68.58" y="187.96" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="7"/>
</segment>
</net>
<net name="ABUS7" class="0">
<segment>
<wire x1="109.22" y1="190.5" x2="106.68" y2="187.96" width="0.1524" layer="91"/>
<wire x1="106.68" y1="187.96" x2="91.44" y2="187.96" width="0.1524" layer="91"/>
<label x="99.06" y="187.96" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="8"/>
</segment>
</net>
<net name="ABUS8" class="0">
<segment>
<wire x1="66.04" y1="187.96" x2="68.58" y2="185.42" width="0.1524" layer="91"/>
<wire x1="68.58" y1="185.42" x2="83.82" y2="185.42" width="0.1524" layer="91"/>
<label x="68.58" y="185.42" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="9"/>
</segment>
</net>
<net name="ABUS9" class="0">
<segment>
<wire x1="109.22" y1="187.96" x2="106.68" y2="185.42" width="0.1524" layer="91"/>
<wire x1="106.68" y1="185.42" x2="91.44" y2="185.42" width="0.1524" layer="91"/>
<label x="99.06" y="185.42" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="10"/>
</segment>
</net>
<net name="ABUS10" class="0">
<segment>
<wire x1="66.04" y1="185.42" x2="68.58" y2="182.88" width="0.1524" layer="91"/>
<wire x1="68.58" y1="182.88" x2="83.82" y2="182.88" width="0.1524" layer="91"/>
<label x="68.58" y="182.88" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="11"/>
</segment>
</net>
<net name="ABUS11" class="0">
<segment>
<wire x1="109.22" y1="185.42" x2="106.68" y2="182.88" width="0.1524" layer="91"/>
<wire x1="106.68" y1="182.88" x2="91.44" y2="182.88" width="0.1524" layer="91"/>
<label x="99.06" y="182.88" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="12"/>
</segment>
</net>
<net name="ABUS12" class="0">
<segment>
<wire x1="66.04" y1="182.88" x2="68.58" y2="180.34" width="0.1524" layer="91"/>
<wire x1="68.58" y1="180.34" x2="83.82" y2="180.34" width="0.1524" layer="91"/>
<label x="68.58" y="180.34" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="13"/>
</segment>
</net>
<net name="ABUS13" class="0">
<segment>
<wire x1="109.22" y1="182.88" x2="106.68" y2="180.34" width="0.1524" layer="91"/>
<wire x1="106.68" y1="180.34" x2="91.44" y2="180.34" width="0.1524" layer="91"/>
<label x="99.06" y="180.34" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="14"/>
</segment>
</net>
<net name="ABUS14" class="0">
<segment>
<wire x1="66.04" y1="180.34" x2="68.58" y2="177.8" width="0.1524" layer="91"/>
<wire x1="68.58" y1="177.8" x2="83.82" y2="177.8" width="0.1524" layer="91"/>
<label x="68.58" y="177.8" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="15"/>
</segment>
</net>
<net name="ABUS15" class="0">
<segment>
<wire x1="109.22" y1="180.34" x2="106.68" y2="177.8" width="0.1524" layer="91"/>
<wire x1="106.68" y1="177.8" x2="91.44" y2="177.8" width="0.1524" layer="91"/>
<label x="99.06" y="177.8" size="1.778" layer="95"/>
<pinref part="JP2" gate="A" pin="16"/>
</segment>
</net>
<net name="RBUS0" class="0">
<segment>
<pinref part="JP4" gate="A" pin="1"/>
<wire x1="132.08" y1="198.12" x2="134.62" y2="195.58" width="0.1524" layer="91"/>
<wire x1="134.62" y1="195.58" x2="152.4" y2="195.58" width="0.1524" layer="91"/>
<label x="134.62" y="195.58" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS1" class="0">
<segment>
<pinref part="JP4" gate="A" pin="2"/>
<wire x1="180.34" y1="198.12" x2="177.8" y2="195.58" width="0.1524" layer="91"/>
<wire x1="177.8" y1="195.58" x2="160.02" y2="195.58" width="0.1524" layer="91"/>
<label x="167.64" y="195.58" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS2" class="0">
<segment>
<pinref part="JP4" gate="A" pin="3"/>
<wire x1="132.08" y1="195.58" x2="134.62" y2="193.04" width="0.1524" layer="91"/>
<wire x1="134.62" y1="193.04" x2="152.4" y2="193.04" width="0.1524" layer="91"/>
<label x="134.62" y="193.04" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS3" class="0">
<segment>
<pinref part="JP4" gate="A" pin="4"/>
<wire x1="180.34" y1="195.58" x2="177.8" y2="193.04" width="0.1524" layer="91"/>
<wire x1="177.8" y1="193.04" x2="160.02" y2="193.04" width="0.1524" layer="91"/>
<label x="167.64" y="193.04" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS4" class="0">
<segment>
<pinref part="JP4" gate="A" pin="5"/>
<wire x1="132.08" y1="193.04" x2="134.62" y2="190.5" width="0.1524" layer="91"/>
<wire x1="134.62" y1="190.5" x2="152.4" y2="190.5" width="0.1524" layer="91"/>
<label x="134.62" y="190.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS5" class="0">
<segment>
<pinref part="JP4" gate="A" pin="6"/>
<wire x1="180.34" y1="193.04" x2="177.8" y2="190.5" width="0.1524" layer="91"/>
<wire x1="177.8" y1="190.5" x2="160.02" y2="190.5" width="0.1524" layer="91"/>
<label x="167.64" y="190.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS6" class="0">
<segment>
<pinref part="JP4" gate="A" pin="7"/>
<wire x1="132.08" y1="190.5" x2="134.62" y2="187.96" width="0.1524" layer="91"/>
<wire x1="134.62" y1="187.96" x2="152.4" y2="187.96" width="0.1524" layer="91"/>
<label x="134.62" y="187.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS7" class="0">
<segment>
<pinref part="JP4" gate="A" pin="8"/>
<wire x1="180.34" y1="190.5" x2="177.8" y2="187.96" width="0.1524" layer="91"/>
<wire x1="177.8" y1="187.96" x2="160.02" y2="187.96" width="0.1524" layer="91"/>
<label x="167.64" y="187.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS8" class="0">
<segment>
<pinref part="JP4" gate="A" pin="9"/>
<wire x1="132.08" y1="187.96" x2="134.62" y2="185.42" width="0.1524" layer="91"/>
<wire x1="134.62" y1="185.42" x2="152.4" y2="185.42" width="0.1524" layer="91"/>
<label x="134.62" y="185.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS9" class="0">
<segment>
<pinref part="JP4" gate="A" pin="10"/>
<wire x1="180.34" y1="187.96" x2="177.8" y2="185.42" width="0.1524" layer="91"/>
<wire x1="177.8" y1="185.42" x2="160.02" y2="185.42" width="0.1524" layer="91"/>
<label x="167.64" y="185.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS10" class="0">
<segment>
<pinref part="JP4" gate="A" pin="11"/>
<wire x1="132.08" y1="185.42" x2="134.62" y2="182.88" width="0.1524" layer="91"/>
<wire x1="134.62" y1="182.88" x2="152.4" y2="182.88" width="0.1524" layer="91"/>
<label x="134.62" y="182.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS11" class="0">
<segment>
<pinref part="JP4" gate="A" pin="12"/>
<wire x1="180.34" y1="185.42" x2="177.8" y2="182.88" width="0.1524" layer="91"/>
<wire x1="177.8" y1="182.88" x2="160.02" y2="182.88" width="0.1524" layer="91"/>
<label x="167.64" y="182.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS12" class="0">
<segment>
<pinref part="JP4" gate="A" pin="13"/>
<wire x1="132.08" y1="182.88" x2="134.62" y2="180.34" width="0.1524" layer="91"/>
<wire x1="134.62" y1="180.34" x2="152.4" y2="180.34" width="0.1524" layer="91"/>
<label x="134.62" y="180.34" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS13" class="0">
<segment>
<pinref part="JP4" gate="A" pin="14"/>
<wire x1="180.34" y1="182.88" x2="177.8" y2="180.34" width="0.1524" layer="91"/>
<wire x1="177.8" y1="180.34" x2="160.02" y2="180.34" width="0.1524" layer="91"/>
<label x="167.64" y="180.34" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS14" class="0">
<segment>
<pinref part="JP4" gate="A" pin="15"/>
<wire x1="132.08" y1="180.34" x2="134.62" y2="177.8" width="0.1524" layer="91"/>
<wire x1="134.62" y1="177.8" x2="152.4" y2="177.8" width="0.1524" layer="91"/>
<label x="134.62" y="177.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="RBUS15" class="0">
<segment>
<pinref part="JP4" gate="A" pin="16"/>
<wire x1="180.34" y1="180.34" x2="177.8" y2="177.8" width="0.1524" layer="91"/>
<wire x1="177.8" y1="177.8" x2="160.02" y2="177.8" width="0.1524" layer="91"/>
<label x="167.64" y="177.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="SUPPLY32" gate="+5V" pin="+5V"/>
<pinref part="VCC1" gate="A" pin="1"/>
<wire x1="10.16" y1="231.14" x2="10.16" y2="228.6" width="0.1524" layer="91"/>
<wire x1="10.16" y1="228.6" x2="17.78" y2="228.6" width="0.1524" layer="91"/>
<wire x1="10.16" y1="228.6" x2="10.16" y2="226.06" width="0.1524" layer="91"/>
<pinref part="VCC1" gate="A" pin="3"/>
<wire x1="10.16" y1="226.06" x2="17.78" y2="226.06" width="0.1524" layer="91"/>
<junction x="10.16" y="228.6"/>
<pinref part="VCC2" gate="A" pin="1"/>
<wire x1="10.16" y1="215.9" x2="17.78" y2="215.9" width="0.1524" layer="91"/>
<wire x1="10.16" y1="215.9" x2="10.16" y2="213.36" width="0.1524" layer="91"/>
<pinref part="VCC2" gate="A" pin="3"/>
<wire x1="10.16" y1="213.36" x2="17.78" y2="213.36" width="0.1524" layer="91"/>
<junction x="10.16" y="215.9"/>
<wire x1="10.16" y1="215.9" x2="10.16" y2="226.06" width="0.1524" layer="91"/>
<junction x="10.16" y="226.06"/>
</segment>
<segment>
<pinref part="VCC1" gate="A" pin="4"/>
<wire x1="25.4" y1="226.06" x2="33.02" y2="226.06" width="0.1524" layer="91"/>
<wire x1="33.02" y1="226.06" x2="33.02" y2="228.6" width="0.1524" layer="91"/>
<pinref part="VCC1" gate="A" pin="2"/>
<wire x1="33.02" y1="228.6" x2="25.4" y2="228.6" width="0.1524" layer="91"/>
<wire x1="33.02" y1="228.6" x2="33.02" y2="231.14" width="0.1524" layer="91"/>
<pinref part="SUPPLY35" gate="+5V" pin="+5V"/>
<junction x="33.02" y="228.6"/>
<pinref part="VCC2" gate="A" pin="4"/>
<wire x1="25.4" y1="213.36" x2="33.02" y2="213.36" width="0.1524" layer="91"/>
<wire x1="33.02" y1="213.36" x2="33.02" y2="215.9" width="0.1524" layer="91"/>
<pinref part="VCC2" gate="A" pin="2"/>
<wire x1="33.02" y1="215.9" x2="25.4" y2="215.9" width="0.1524" layer="91"/>
<junction x="33.02" y="215.9"/>
<wire x1="33.02" y1="215.9" x2="33.02" y2="226.06" width="0.1524" layer="91"/>
<junction x="33.02" y="226.06"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="GND1" gate="A" pin="1"/>
<wire x1="10.16" y1="198.12" x2="17.78" y2="198.12" width="0.1524" layer="91"/>
<wire x1="10.16" y1="198.12" x2="10.16" y2="195.58" width="0.1524" layer="91"/>
<pinref part="GND1" gate="A" pin="3"/>
<wire x1="10.16" y1="195.58" x2="17.78" y2="195.58" width="0.1524" layer="91"/>
<pinref part="GND2" gate="A" pin="1"/>
<wire x1="10.16" y1="185.42" x2="17.78" y2="185.42" width="0.1524" layer="91"/>
<wire x1="10.16" y1="185.42" x2="10.16" y2="182.88" width="0.1524" layer="91"/>
<pinref part="GND2" gate="A" pin="3"/>
<wire x1="10.16" y1="182.88" x2="17.78" y2="182.88" width="0.1524" layer="91"/>
<junction x="10.16" y="185.42"/>
<wire x1="10.16" y1="185.42" x2="10.16" y2="195.58" width="0.1524" layer="91"/>
<junction x="10.16" y="195.58"/>
<pinref part="SUPPLY36" gate="GND" pin="GND"/>
<wire x1="10.16" y1="177.8" x2="10.16" y2="182.88" width="0.1524" layer="91"/>
<junction x="10.16" y="182.88"/>
</segment>
<segment>
<pinref part="GND1" gate="A" pin="4"/>
<wire x1="25.4" y1="195.58" x2="33.02" y2="195.58" width="0.1524" layer="91"/>
<wire x1="33.02" y1="195.58" x2="33.02" y2="198.12" width="0.1524" layer="91"/>
<pinref part="GND1" gate="A" pin="2"/>
<wire x1="33.02" y1="198.12" x2="25.4" y2="198.12" width="0.1524" layer="91"/>
<pinref part="GND2" gate="A" pin="4"/>
<wire x1="25.4" y1="182.88" x2="33.02" y2="182.88" width="0.1524" layer="91"/>
<wire x1="33.02" y1="182.88" x2="33.02" y2="185.42" width="0.1524" layer="91"/>
<pinref part="GND2" gate="A" pin="2"/>
<wire x1="33.02" y1="185.42" x2="25.4" y2="185.42" width="0.1524" layer="91"/>
<junction x="33.02" y="185.42"/>
<wire x1="33.02" y1="185.42" x2="33.02" y2="195.58" width="0.1524" layer="91"/>
<junction x="33.02" y="195.58"/>
<pinref part="SUPPLY37" gate="GND" pin="GND"/>
<wire x1="33.02" y1="177.8" x2="33.02" y2="182.88" width="0.1524" layer="91"/>
<junction x="33.02" y="182.88"/>
</segment>
</net>
<net name="/RST" class="0">
<segment>
<wire x1="83.82" y1="144.78" x2="73.66" y2="144.78" width="0.1524" layer="91"/>
<label x="73.66" y="144.78" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP10" gate="A" pin="7"/>
</segment>
</net>
<net name="CLK1" class="0">
<segment>
<wire x1="91.44" y1="142.24" x2="101.6" y2="142.24" width="0.1524" layer="91"/>
<label x="101.6" y="142.24" size="1.27" layer="95" xref="yes"/>
<pinref part="JP10" gate="A" pin="10"/>
</segment>
</net>
<net name="CLK0A" class="0">
<segment>
<wire x1="83.82" y1="137.16" x2="73.66" y2="137.16" width="0.1524" layer="91"/>
<label x="73.66" y="137.16" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP10" gate="A" pin="13"/>
</segment>
</net>
<net name="CLK0B" class="0">
<segment>
<wire x1="91.44" y1="132.08" x2="101.6" y2="132.08" width="0.1524" layer="91"/>
<label x="101.6" y="132.08" size="1.27" layer="95" xref="yes"/>
<pinref part="JP10" gate="A" pin="18"/>
</segment>
</net>
<net name="CLK0C" class="0">
<segment>
<wire x1="83.82" y1="129.54" x2="73.66" y2="129.54" width="0.1524" layer="91"/>
<label x="73.66" y="129.54" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP10" gate="A" pin="19"/>
</segment>
</net>
<net name="BUSCLKA" class="0">
<segment>
<wire x1="83.82" y1="124.46" x2="73.66" y2="124.46" width="0.1524" layer="91"/>
<label x="73.66" y="124.46" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP10" gate="A" pin="23"/>
</segment>
</net>
<net name="BUSCLKB" class="0">
<segment>
<wire x1="91.44" y1="124.46" x2="101.6" y2="124.46" width="0.1524" layer="91"/>
<label x="101.6" y="124.46" size="1.27" layer="95" xref="yes"/>
<pinref part="JP10" gate="A" pin="24"/>
</segment>
</net>
<net name="RST" class="0">
<segment>
<wire x1="83.82" y1="142.24" x2="73.66" y2="142.24" width="0.1524" layer="91"/>
<label x="73.66" y="142.24" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP10" gate="A" pin="9"/>
</segment>
</net>
<net name="IRQ0" class="0">
<segment>
<wire x1="91.44" y1="233.68" x2="106.68" y2="233.68" width="0.1524" layer="91"/>
<wire x1="106.68" y1="233.68" x2="109.22" y2="236.22" width="0.1524" layer="91"/>
<label x="101.6" y="233.68" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="2"/>
</segment>
</net>
<net name="IRQ1" class="0">
<segment>
<wire x1="91.44" y1="231.14" x2="106.68" y2="231.14" width="0.1524" layer="91"/>
<wire x1="106.68" y1="231.14" x2="109.22" y2="233.68" width="0.1524" layer="91"/>
<label x="101.6" y="231.14" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="4"/>
</segment>
</net>
<net name="IRQ2" class="0">
<segment>
<wire x1="91.44" y1="228.6" x2="106.68" y2="228.6" width="0.1524" layer="91"/>
<wire x1="106.68" y1="228.6" x2="109.22" y2="231.14" width="0.1524" layer="91"/>
<label x="101.6" y="228.6" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="6"/>
</segment>
</net>
<net name="IRQ3" class="0">
<segment>
<wire x1="91.44" y1="226.06" x2="106.68" y2="226.06" width="0.1524" layer="91"/>
<wire x1="106.68" y1="226.06" x2="109.22" y2="228.6" width="0.1524" layer="91"/>
<label x="101.6" y="226.06" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="8"/>
</segment>
</net>
<net name="IRQ4" class="0">
<segment>
<wire x1="91.44" y1="223.52" x2="106.68" y2="223.52" width="0.1524" layer="91"/>
<wire x1="106.68" y1="223.52" x2="109.22" y2="226.06" width="0.1524" layer="91"/>
<label x="101.6" y="223.52" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="10"/>
</segment>
</net>
<net name="IRQ5" class="0">
<segment>
<wire x1="91.44" y1="220.98" x2="106.68" y2="220.98" width="0.1524" layer="91"/>
<wire x1="106.68" y1="220.98" x2="109.22" y2="223.52" width="0.1524" layer="91"/>
<label x="101.6" y="220.98" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="12"/>
</segment>
</net>
<net name="IRQ6" class="0">
<segment>
<wire x1="109.22" y1="220.98" x2="106.68" y2="218.44" width="0.1524" layer="91"/>
<wire x1="106.68" y1="218.44" x2="91.44" y2="218.44" width="0.1524" layer="91"/>
<label x="101.6" y="218.44" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="14"/>
</segment>
</net>
<net name="IRQ7" class="0">
<segment>
<wire x1="109.22" y1="218.44" x2="106.68" y2="215.9" width="0.1524" layer="91"/>
<wire x1="106.68" y1="215.9" x2="91.44" y2="215.9" width="0.1524" layer="91"/>
<label x="101.6" y="215.9" size="1.778" layer="95"/>
<pinref part="JP1" gate="A" pin="16"/>
</segment>
</net>
<net name="/FS" class="0">
<segment>
<wire x1="91.44" y1="116.84" x2="101.6" y2="116.84" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="30"/>
<label x="101.6" y="116.84" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="/ENMEM" class="0">
<segment>
<wire x1="91.44" y1="134.62" x2="101.6" y2="134.62" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="16"/>
<label x="101.6" y="134.62" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="/LDMEM" class="0">
<segment>
<wire x1="83.82" y1="134.62" x2="73.66" y2="134.62" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="15"/>
<label x="73.66" y="134.62" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="MEMSEG" class="0">
<segment>
<wire x1="91.44" y1="137.16" x2="101.6" y2="137.16" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="14"/>
<label x="101.6" y="137.16" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="/FI" class="0">
<segment>
<wire x1="91.44" y1="114.3" x2="101.6" y2="114.3" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="32"/>
<label x="101.6" y="114.3" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="CLK0D" class="0">
<segment>
<wire x1="83.82" y1="132.08" x2="73.66" y2="132.08" width="0.1524" layer="91"/>
<label x="73.66" y="132.08" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP10" gate="A" pin="17"/>
</segment>
</net>
<net name="FC" class="0">
<segment>
<wire x1="91.44" y1="152.4" x2="101.6" y2="152.4" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="2"/>
<label x="101.6" y="152.4" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="FZ" class="0">
<segment>
<wire x1="91.44" y1="149.86" x2="101.6" y2="149.86" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="4"/>
<label x="101.6" y="149.86" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="FN" class="0">
<segment>
<wire x1="91.44" y1="147.32" x2="101.6" y2="147.32" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="6"/>
<label x="101.6" y="147.32" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="FV" class="0">
<segment>
<wire x1="91.44" y1="144.78" x2="101.6" y2="144.78" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="8"/>
<label x="101.6" y="144.78" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="SP_DIR" class="0">
<segment>
<wire x1="91.44" y1="129.54" x2="101.6" y2="129.54" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="20"/>
<label x="101.6" y="129.54" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="/CNTSP" class="0">
<segment>
<wire x1="83.82" y1="149.86" x2="73.66" y2="149.86" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="3"/>
<label x="73.66" y="149.86" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/INCPC" class="0">
<segment>
<wire x1="83.82" y1="152.4" x2="73.66" y2="152.4" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="1"/>
<label x="73.66" y="152.4" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="PROT" class="0">
<segment>
<wire x1="83.82" y1="127" x2="73.66" y2="127" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="21"/>
<label x="73.66" y="127" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/LATCHFLAGS" class="0">
<segment>
<wire x1="91.44" y1="139.7" x2="101.6" y2="139.7" width="0.1524" layer="91"/>
<pinref part="JP10" gate="A" pin="12"/>
<label x="101.6" y="139.7" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="FAULT" class="0">
<segment>
<pinref part="JP10" gate="A" pin="28"/>
<wire x1="91.44" y1="119.38" x2="101.6" y2="119.38" width="0.1524" layer="91"/>
<label x="101.6" y="119.38" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="/LOAD_IR" class="0">
<segment>
<pinref part="JP10" gate="A" pin="26"/>
<wire x1="91.44" y1="121.92" x2="101.6" y2="121.92" width="0.1524" layer="91"/>
<label x="101.6" y="121.92" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="/BUSIFCEN" class="0">
<segment>
<pinref part="JP10" gate="A" pin="5"/>
<wire x1="83.82" y1="147.32" x2="73.66" y2="147.32" width="0.1524" layer="91"/>
<label x="73.66" y="147.32" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/FP" class="0">
<segment>
<pinref part="JP10" gate="A" pin="34"/>
<wire x1="91.44" y1="111.76" x2="101.6" y2="111.76" width="0.1524" layer="91"/>
<label x="101.6" y="111.76" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="/NP_FAULT" class="0">
<segment>
<pinref part="JP10" gate="A" pin="36"/>
<wire x1="91.44" y1="109.22" x2="101.6" y2="109.22" width="0.1524" layer="91"/>
<label x="101.6" y="109.22" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="/WR_FAULT" class="0">
<segment>
<pinref part="JP10" gate="A" pin="33"/>
<wire x1="83.82" y1="111.76" x2="73.66" y2="111.76" width="0.1524" layer="91"/>
<label x="73.66" y="111.76" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="/IO" class="0">
<segment>
<pinref part="JP10" gate="A" pin="35"/>
<wire x1="83.82" y1="109.22" x2="73.66" y2="109.22" width="0.1524" layer="91"/>
<label x="73.66" y="109.22" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="PABUS12" class="0">
<segment>
<pinref part="JP5" gate="A" pin="1"/>
<wire x1="132.08" y1="154.94" x2="134.62" y2="152.4" width="0.1524" layer="91"/>
<wire x1="134.62" y1="152.4" x2="152.4" y2="152.4" width="0.1524" layer="91"/>
<label x="134.62" y="152.4" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS13" class="0">
<segment>
<pinref part="JP5" gate="A" pin="2"/>
<wire x1="180.34" y1="154.94" x2="177.8" y2="152.4" width="0.1524" layer="91"/>
<wire x1="177.8" y1="152.4" x2="160.02" y2="152.4" width="0.1524" layer="91"/>
<label x="165.1" y="152.4" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS14" class="0">
<segment>
<pinref part="JP5" gate="A" pin="3"/>
<wire x1="132.08" y1="152.4" x2="134.62" y2="149.86" width="0.1524" layer="91"/>
<wire x1="134.62" y1="149.86" x2="152.4" y2="149.86" width="0.1524" layer="91"/>
<label x="134.62" y="149.86" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS15" class="0">
<segment>
<pinref part="JP5" gate="A" pin="4"/>
<wire x1="180.34" y1="152.4" x2="177.8" y2="149.86" width="0.1524" layer="91"/>
<wire x1="177.8" y1="149.86" x2="160.02" y2="149.86" width="0.1524" layer="91"/>
<label x="165.1" y="149.86" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS16" class="0">
<segment>
<pinref part="JP5" gate="A" pin="5"/>
<wire x1="132.08" y1="149.86" x2="134.62" y2="147.32" width="0.1524" layer="91"/>
<wire x1="134.62" y1="147.32" x2="152.4" y2="147.32" width="0.1524" layer="91"/>
<label x="134.62" y="147.32" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS18" class="0">
<segment>
<pinref part="JP5" gate="A" pin="7"/>
<wire x1="132.08" y1="147.32" x2="134.62" y2="144.78" width="0.1524" layer="91"/>
<wire x1="134.62" y1="144.78" x2="152.4" y2="144.78" width="0.1524" layer="91"/>
<label x="134.62" y="144.78" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS20" class="0">
<segment>
<pinref part="JP5" gate="A" pin="9"/>
<wire x1="132.08" y1="144.78" x2="134.62" y2="142.24" width="0.1524" layer="91"/>
<wire x1="134.62" y1="142.24" x2="152.4" y2="142.24" width="0.1524" layer="91"/>
<label x="134.62" y="142.24" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS17" class="0">
<segment>
<pinref part="JP5" gate="A" pin="6"/>
<wire x1="180.34" y1="149.86" x2="177.8" y2="147.32" width="0.1524" layer="91"/>
<wire x1="177.8" y1="147.32" x2="160.02" y2="147.32" width="0.1524" layer="91"/>
<label x="165.1" y="147.32" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS19" class="0">
<segment>
<pinref part="JP5" gate="A" pin="8"/>
<wire x1="180.34" y1="147.32" x2="177.8" y2="144.78" width="0.1524" layer="91"/>
<wire x1="177.8" y1="144.78" x2="160.02" y2="144.78" width="0.1524" layer="91"/>
<label x="165.1" y="144.78" size="1.778" layer="95"/>
</segment>
</net>
<net name="PABUS21" class="0">
<segment>
<pinref part="JP5" gate="A" pin="10"/>
<wire x1="180.34" y1="144.78" x2="177.8" y2="142.24" width="0.1524" layer="91"/>
<wire x1="177.8" y1="142.24" x2="160.02" y2="142.24" width="0.1524" layer="91"/>
<label x="165.1" y="142.24" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
