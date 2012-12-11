<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
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
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Atmel_MCUs">
<packages>
<package name="TQFP144">
<description>&lt;b&gt;QFP144&lt;/b&gt;&lt;p&gt;
shrink quad flat pack, square (smd-ipc)</description>
<wire x1="-9.91" y1="-9.91" x2="9.91" y2="-9.91" width="0.2032" layer="51"/>
<wire x1="9.91" y1="-9.91" x2="9.91" y2="9.91" width="0.2032" layer="51"/>
<wire x1="9.91" y1="9.91" x2="-9.91" y2="9.91" width="0.2032" layer="51"/>
<wire x1="-9.91" y1="9.91" x2="-9.91" y2="-9.91" width="0.2032" layer="51"/>
<wire x1="-9.72" y1="9.71" x2="9.71" y2="9.71" width="0.2032" layer="21"/>
<wire x1="9.71" y1="9.71" x2="9.71" y2="-9.71" width="0.2032" layer="21"/>
<wire x1="9.71" y1="-9.71" x2="-9.72" y2="-9.71" width="0.2032" layer="21"/>
<wire x1="-9.72" y1="-9.71" x2="-9.72" y2="9.71" width="0.2032" layer="21"/>
<circle x="-8.5001" y="-8.5001" radius="0.7501" width="0.254" layer="21"/>
<smd name="1" x="-8.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="2" x="-8.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="3" x="-7.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="4" x="-7.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="5" x="-6.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="6" x="-6.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="7" x="-5.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="8" x="-5.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="9" x="-4.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="10" x="-4.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="11" x="-3.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="12" x="-3.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="13" x="-2.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="14" x="-2.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="15" x="-1.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="16" x="-1.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="17" x="-0.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="18" x="-0.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="19" x="0.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="20" x="0.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="21" x="1.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="22" x="1.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="23" x="2.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="24" x="2.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="25" x="3.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="26" x="3.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="27" x="4.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="28" x="4.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="29" x="5.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="30" x="5.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="31" x="6.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="32" x="6.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="33" x="7.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="34" x="7.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="35" x="8.25" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="36" x="8.75" y="-10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="37" x="10.6" y="-8.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="38" x="10.6" y="-8.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="39" x="10.6" y="-7.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="40" x="10.6" y="-7.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="41" x="10.6" y="-6.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="42" x="10.6" y="-6.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="43" x="10.6" y="-5.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="44" x="10.6" y="-5.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="45" x="10.6" y="-4.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="46" x="10.6" y="-4.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="47" x="10.6" y="-3.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="48" x="10.6" y="-3.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="49" x="10.6" y="-2.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="50" x="10.6" y="-2.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="51" x="10.6" y="-1.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="52" x="10.6" y="-1.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="53" x="10.6" y="-0.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="54" x="10.6" y="-0.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="55" x="10.6" y="0.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="56" x="10.6" y="0.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="57" x="10.6" y="1.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="58" x="10.6" y="1.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="59" x="10.6" y="2.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="60" x="10.6" y="2.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="61" x="10.6" y="3.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="62" x="10.6" y="3.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="63" x="10.6" y="4.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="64" x="10.6" y="4.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="65" x="10.6" y="5.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="66" x="10.6" y="5.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="67" x="10.6" y="6.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="68" x="10.6" y="6.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="69" x="10.6" y="7.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="70" x="10.6" y="7.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="71" x="10.6" y="8.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="72" x="10.6" y="8.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="73" x="8.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="74" x="8.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="75" x="7.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="76" x="7.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="77" x="6.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="78" x="6.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="79" x="5.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="80" x="5.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="81" x="4.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="82" x="4.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="83" x="3.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="84" x="3.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="85" x="2.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="86" x="2.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="87" x="1.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="88" x="1.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="89" x="0.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="90" x="0.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="91" x="-0.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="92" x="-0.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="93" x="-1.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="94" x="-1.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="95" x="-2.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="96" x="-2.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="97" x="-3.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="98" x="-3.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="99" x="-4.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="100" x="-4.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="101" x="-5.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="102" x="-5.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="103" x="-6.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="104" x="-6.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="105" x="-7.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="106" x="-7.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="107" x="-8.25" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="108" x="-8.75" y="10.6" dx="0.3" dy="1.6" layer="1"/>
<smd name="109" x="-10.6" y="8.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="110" x="-10.6" y="8.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="111" x="-10.6" y="7.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="112" x="-10.6" y="7.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="113" x="-10.6" y="6.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="114" x="-10.6" y="6.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="115" x="-10.6" y="5.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="116" x="-10.6" y="5.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="117" x="-10.6" y="4.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="118" x="-10.6" y="4.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="119" x="-10.6" y="3.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="120" x="-10.6" y="3.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="121" x="-10.6" y="2.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="122" x="-10.6" y="2.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="123" x="-10.6" y="1.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="124" x="-10.6" y="1.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="125" x="-10.6" y="0.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="126" x="-10.6" y="0.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="127" x="-10.6" y="-0.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="128" x="-10.6" y="-0.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="129" x="-10.6" y="-1.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="130" x="-10.6" y="-1.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="131" x="-10.6" y="-2.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="132" x="-10.6" y="-2.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="133" x="-10.6" y="-3.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="134" x="-10.6" y="-3.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="135" x="-10.6" y="-4.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="136" x="-10.6" y="-4.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="137" x="-10.6" y="-5.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="138" x="-10.6" y="-5.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="139" x="-10.6" y="-6.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="140" x="-10.6" y="-6.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="141" x="-10.6" y="-7.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="142" x="-10.6" y="-7.75" dx="1.6" dy="0.3" layer="1"/>
<smd name="143" x="-10.6" y="-8.25" dx="1.6" dy="0.3" layer="1"/>
<smd name="144" x="-10.6" y="-8.75" dx="1.6" dy="0.3" layer="1"/>
<text x="-3.81" y="-3.175" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.81" y="1.905" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-8.8999" y1="-10.8999" x2="-8.5999" y2="-9.9499" layer="51"/>
<rectangle x1="-8.4" y1="-10.8999" x2="-8.1001" y2="-9.9499" layer="51"/>
<rectangle x1="-7.8999" y1="-10.8999" x2="-7.5999" y2="-9.9499" layer="51"/>
<rectangle x1="-7.4" y1="-10.8999" x2="-7.1001" y2="-9.9499" layer="51"/>
<rectangle x1="-6.8999" y1="-10.8999" x2="-6.5999" y2="-9.9499" layer="51"/>
<rectangle x1="-6.4" y1="-10.8999" x2="-6.1001" y2="-9.9499" layer="51"/>
<rectangle x1="-5.8999" y1="-10.8999" x2="-5.5999" y2="-9.9499" layer="51"/>
<rectangle x1="-5.4" y1="-10.8999" x2="-5.1001" y2="-9.9499" layer="51"/>
<rectangle x1="-4.8999" y1="-10.8999" x2="-4.5999" y2="-9.9499" layer="51"/>
<rectangle x1="-4.4" y1="-10.8999" x2="-4.1001" y2="-9.9499" layer="51"/>
<rectangle x1="-3.8999" y1="-10.8999" x2="-3.5999" y2="-9.9499" layer="51"/>
<rectangle x1="-3.4" y1="-10.8999" x2="-3.1001" y2="-9.9499" layer="51"/>
<rectangle x1="-2.8999" y1="-10.8999" x2="-2.5999" y2="-9.9499" layer="51"/>
<rectangle x1="-2.4" y1="-10.8999" x2="-2.1001" y2="-9.9499" layer="51"/>
<rectangle x1="-1.8999" y1="-10.8999" x2="-1.5999" y2="-9.9499" layer="51"/>
<rectangle x1="-1.4" y1="-10.8999" x2="-1.1001" y2="-9.9499" layer="51"/>
<rectangle x1="-0.8999" y1="-10.8999" x2="-0.5999" y2="-9.9499" layer="51"/>
<rectangle x1="-0.4001" y1="-10.8999" x2="-0.1001" y2="-9.9499" layer="51"/>
<rectangle x1="0.1001" y1="-10.8999" x2="0.4001" y2="-9.9499" layer="51"/>
<rectangle x1="0.5999" y1="-10.8999" x2="0.8999" y2="-9.9499" layer="51"/>
<rectangle x1="1.1001" y1="-10.8999" x2="1.4" y2="-9.9499" layer="51"/>
<rectangle x1="1.5999" y1="-10.8999" x2="1.8999" y2="-9.9499" layer="51"/>
<rectangle x1="2.1001" y1="-10.8999" x2="2.4" y2="-9.9499" layer="51"/>
<rectangle x1="2.5999" y1="-10.8999" x2="2.8999" y2="-9.9499" layer="51"/>
<rectangle x1="3.1001" y1="-10.8999" x2="3.4" y2="-9.9499" layer="51"/>
<rectangle x1="3.5999" y1="-10.8999" x2="3.8999" y2="-9.9499" layer="51"/>
<rectangle x1="4.1001" y1="-10.8999" x2="4.4" y2="-9.9499" layer="51"/>
<rectangle x1="4.5999" y1="-10.8999" x2="4.8999" y2="-9.9499" layer="51"/>
<rectangle x1="5.1001" y1="-10.8999" x2="5.4" y2="-9.9499" layer="51"/>
<rectangle x1="5.5999" y1="-10.8999" x2="5.8999" y2="-9.9499" layer="51"/>
<rectangle x1="6.1001" y1="-10.8999" x2="6.4" y2="-9.9499" layer="51"/>
<rectangle x1="6.5999" y1="-10.8999" x2="6.8999" y2="-9.9499" layer="51"/>
<rectangle x1="7.1001" y1="-10.8999" x2="7.4" y2="-9.9499" layer="51"/>
<rectangle x1="7.5999" y1="-10.8999" x2="7.8999" y2="-9.9499" layer="51"/>
<rectangle x1="8.1001" y1="-10.8999" x2="8.4" y2="-9.9499" layer="51"/>
<rectangle x1="8.5999" y1="-10.8999" x2="8.8999" y2="-9.9499" layer="51"/>
<rectangle x1="9.9499" y1="-8.8999" x2="10.8999" y2="-8.5999" layer="51"/>
<rectangle x1="9.9499" y1="-8.4" x2="10.8999" y2="-8.1001" layer="51"/>
<rectangle x1="9.9499" y1="-7.8999" x2="10.8999" y2="-7.5999" layer="51"/>
<rectangle x1="9.9499" y1="-7.4" x2="10.8999" y2="-7.1001" layer="51"/>
<rectangle x1="9.9499" y1="-6.8999" x2="10.8999" y2="-6.5999" layer="51"/>
<rectangle x1="9.9499" y1="-6.4" x2="10.8999" y2="-6.1001" layer="51"/>
<rectangle x1="9.9499" y1="-5.8999" x2="10.8999" y2="-5.5999" layer="51"/>
<rectangle x1="9.9499" y1="-5.4" x2="10.8999" y2="-5.1001" layer="51"/>
<rectangle x1="9.9499" y1="-4.8999" x2="10.8999" y2="-4.5999" layer="51"/>
<rectangle x1="9.9499" y1="-4.4" x2="10.8999" y2="-4.1001" layer="51"/>
<rectangle x1="9.9499" y1="-3.8999" x2="10.8999" y2="-3.5999" layer="51"/>
<rectangle x1="9.9499" y1="-3.4" x2="10.8999" y2="-3.1001" layer="51"/>
<rectangle x1="9.9499" y1="-2.8999" x2="10.8999" y2="-2.5999" layer="51"/>
<rectangle x1="9.9499" y1="-2.4" x2="10.8999" y2="-2.1001" layer="51"/>
<rectangle x1="9.9499" y1="-1.8999" x2="10.8999" y2="-1.5999" layer="51"/>
<rectangle x1="9.9499" y1="-1.4" x2="10.8999" y2="-1.1001" layer="51"/>
<rectangle x1="9.9499" y1="-0.8999" x2="10.8999" y2="-0.5999" layer="51"/>
<rectangle x1="9.9499" y1="-0.4001" x2="10.8999" y2="-0.1001" layer="51"/>
<rectangle x1="9.9499" y1="0.1001" x2="10.8999" y2="0.4001" layer="51"/>
<rectangle x1="9.9499" y1="0.5999" x2="10.8999" y2="0.8999" layer="51"/>
<rectangle x1="9.9499" y1="1.1001" x2="10.8999" y2="1.4" layer="51"/>
<rectangle x1="9.9499" y1="1.5999" x2="10.8999" y2="1.8999" layer="51"/>
<rectangle x1="9.9499" y1="2.1001" x2="10.8999" y2="2.4" layer="51"/>
<rectangle x1="9.9499" y1="2.5999" x2="10.8999" y2="2.8999" layer="51"/>
<rectangle x1="9.9499" y1="3.1001" x2="10.8999" y2="3.4" layer="51"/>
<rectangle x1="9.9499" y1="3.5999" x2="10.8999" y2="3.8999" layer="51"/>
<rectangle x1="9.9499" y1="4.1001" x2="10.8999" y2="4.4" layer="51"/>
<rectangle x1="9.9499" y1="4.5999" x2="10.8999" y2="4.8999" layer="51"/>
<rectangle x1="9.9499" y1="5.1001" x2="10.8999" y2="5.4" layer="51"/>
<rectangle x1="9.9499" y1="5.5999" x2="10.8999" y2="5.8999" layer="51"/>
<rectangle x1="9.9499" y1="6.1001" x2="10.8999" y2="6.4" layer="51"/>
<rectangle x1="9.9499" y1="6.5999" x2="10.8999" y2="6.8999" layer="51"/>
<rectangle x1="9.9499" y1="7.1001" x2="10.8999" y2="7.4" layer="51"/>
<rectangle x1="9.9499" y1="7.5999" x2="10.8999" y2="7.8999" layer="51"/>
<rectangle x1="9.9499" y1="8.1001" x2="10.8999" y2="8.4" layer="51"/>
<rectangle x1="9.9499" y1="8.5999" x2="10.8999" y2="8.8999" layer="51"/>
<rectangle x1="8.5999" y1="9.9499" x2="8.8999" y2="10.8999" layer="51"/>
<rectangle x1="8.1001" y1="9.9499" x2="8.4" y2="10.8999" layer="51"/>
<rectangle x1="7.5999" y1="9.9499" x2="7.8999" y2="10.8999" layer="51"/>
<rectangle x1="7.1001" y1="9.9499" x2="7.4" y2="10.8999" layer="51"/>
<rectangle x1="6.5999" y1="9.9499" x2="6.8999" y2="10.8999" layer="51"/>
<rectangle x1="6.1001" y1="9.9499" x2="6.4" y2="10.8999" layer="51"/>
<rectangle x1="5.5999" y1="9.9499" x2="5.8999" y2="10.8999" layer="51"/>
<rectangle x1="5.1001" y1="9.9499" x2="5.4" y2="10.8999" layer="51"/>
<rectangle x1="4.5999" y1="9.9499" x2="4.8999" y2="10.8999" layer="51"/>
<rectangle x1="4.1001" y1="9.9499" x2="4.4" y2="10.8999" layer="51"/>
<rectangle x1="3.5999" y1="9.9499" x2="3.8999" y2="10.8999" layer="51"/>
<rectangle x1="3.1001" y1="9.9499" x2="3.4" y2="10.8999" layer="51"/>
<rectangle x1="2.5999" y1="9.9499" x2="2.8999" y2="10.8999" layer="51"/>
<rectangle x1="2.1001" y1="9.9499" x2="2.4" y2="10.8999" layer="51"/>
<rectangle x1="1.5999" y1="9.9499" x2="1.8999" y2="10.8999" layer="51"/>
<rectangle x1="1.1001" y1="9.9499" x2="1.4" y2="10.8999" layer="51"/>
<rectangle x1="0.5999" y1="9.9499" x2="0.8999" y2="10.8999" layer="51"/>
<rectangle x1="0.1001" y1="9.9499" x2="0.4001" y2="10.8999" layer="51"/>
<rectangle x1="-0.4001" y1="9.9499" x2="-0.1001" y2="10.8999" layer="51"/>
<rectangle x1="-0.8999" y1="9.9499" x2="-0.5999" y2="10.8999" layer="51"/>
<rectangle x1="-1.4" y1="9.9499" x2="-1.1001" y2="10.8999" layer="51"/>
<rectangle x1="-1.8999" y1="9.9499" x2="-1.5999" y2="10.8999" layer="51"/>
<rectangle x1="-2.4" y1="9.9499" x2="-2.1001" y2="10.8999" layer="51"/>
<rectangle x1="-2.8999" y1="9.9499" x2="-2.5999" y2="10.8999" layer="51"/>
<rectangle x1="-3.4" y1="9.9499" x2="-3.1001" y2="10.8999" layer="51"/>
<rectangle x1="-3.8999" y1="9.9499" x2="-3.5999" y2="10.8999" layer="51"/>
<rectangle x1="-4.4" y1="9.9499" x2="-4.1001" y2="10.8999" layer="51"/>
<rectangle x1="-4.8999" y1="9.9499" x2="-4.5999" y2="10.8999" layer="51"/>
<rectangle x1="-5.4" y1="9.9499" x2="-5.1001" y2="10.8999" layer="51"/>
<rectangle x1="-5.8999" y1="9.9499" x2="-5.5999" y2="10.8999" layer="51"/>
<rectangle x1="-6.4" y1="9.9499" x2="-6.1001" y2="10.8999" layer="51"/>
<rectangle x1="-6.8999" y1="9.9499" x2="-6.5999" y2="10.8999" layer="51"/>
<rectangle x1="-7.4" y1="9.9499" x2="-7.1001" y2="10.8999" layer="51"/>
<rectangle x1="-7.8999" y1="9.9499" x2="-7.5999" y2="10.8999" layer="51"/>
<rectangle x1="-8.4" y1="9.9499" x2="-8.1001" y2="10.8999" layer="51"/>
<rectangle x1="-8.8999" y1="9.9499" x2="-8.5999" y2="10.8999" layer="51"/>
<rectangle x1="-10.8999" y1="8.5999" x2="-9.9499" y2="8.8999" layer="51"/>
<rectangle x1="-10.8999" y1="8.1001" x2="-9.9499" y2="8.4" layer="51"/>
<rectangle x1="-10.8999" y1="7.5999" x2="-9.9499" y2="7.8999" layer="51"/>
<rectangle x1="-10.8999" y1="7.1001" x2="-9.9499" y2="7.4" layer="51"/>
<rectangle x1="-10.8999" y1="6.5999" x2="-9.9499" y2="6.8999" layer="51"/>
<rectangle x1="-10.8999" y1="6.1001" x2="-9.9499" y2="6.4" layer="51"/>
<rectangle x1="-10.8999" y1="5.5999" x2="-9.9499" y2="5.8999" layer="51"/>
<rectangle x1="-10.8999" y1="5.1001" x2="-9.9499" y2="5.4" layer="51"/>
<rectangle x1="-10.8999" y1="4.5999" x2="-9.9499" y2="4.8999" layer="51"/>
<rectangle x1="-10.8999" y1="4.1001" x2="-9.9499" y2="4.4" layer="51"/>
<rectangle x1="-10.8999" y1="3.5999" x2="-9.9499" y2="3.8999" layer="51"/>
<rectangle x1="-10.8999" y1="3.1001" x2="-9.9499" y2="3.4" layer="51"/>
<rectangle x1="-10.8999" y1="2.5999" x2="-9.9499" y2="2.8999" layer="51"/>
<rectangle x1="-10.8999" y1="2.1001" x2="-9.9499" y2="2.4" layer="51"/>
<rectangle x1="-10.8999" y1="1.5999" x2="-9.9499" y2="1.8999" layer="51"/>
<rectangle x1="-10.8999" y1="1.1001" x2="-9.9499" y2="1.4" layer="51"/>
<rectangle x1="-10.8999" y1="0.5999" x2="-9.9499" y2="0.8999" layer="51"/>
<rectangle x1="-10.8999" y1="0.1001" x2="-9.9499" y2="0.4001" layer="51"/>
<rectangle x1="-10.8999" y1="-0.4001" x2="-9.9499" y2="-0.1001" layer="51"/>
<rectangle x1="-10.8999" y1="-0.8999" x2="-9.9499" y2="-0.5999" layer="51"/>
<rectangle x1="-10.8999" y1="-1.4" x2="-9.9499" y2="-1.1001" layer="51"/>
<rectangle x1="-10.8999" y1="-1.8999" x2="-9.9499" y2="-1.5999" layer="51"/>
<rectangle x1="-10.8999" y1="-2.4" x2="-9.9499" y2="-2.1001" layer="51"/>
<rectangle x1="-10.8999" y1="-2.8999" x2="-9.9499" y2="-2.5999" layer="51"/>
<rectangle x1="-10.8999" y1="-3.4" x2="-9.9499" y2="-3.1001" layer="51"/>
<rectangle x1="-10.8999" y1="-3.8999" x2="-9.9499" y2="-3.5999" layer="51"/>
<rectangle x1="-10.8999" y1="-4.4" x2="-9.9499" y2="-4.1001" layer="51"/>
<rectangle x1="-10.8999" y1="-4.8999" x2="-9.9499" y2="-4.5999" layer="51"/>
<rectangle x1="-10.8999" y1="-5.4" x2="-9.9499" y2="-5.1001" layer="51"/>
<rectangle x1="-10.8999" y1="-5.8999" x2="-9.9499" y2="-5.5999" layer="51"/>
<rectangle x1="-10.8999" y1="-6.4" x2="-9.9499" y2="-6.1001" layer="51"/>
<rectangle x1="-10.8999" y1="-6.8999" x2="-9.9499" y2="-6.5999" layer="51"/>
<rectangle x1="-10.8999" y1="-7.4" x2="-9.9499" y2="-7.1001" layer="51"/>
<rectangle x1="-10.8999" y1="-7.8999" x2="-9.9499" y2="-7.5999" layer="51"/>
<rectangle x1="-10.8999" y1="-8.4" x2="-9.9499" y2="-8.1001" layer="51"/>
<rectangle x1="-10.8999" y1="-8.8999" x2="-9.9499" y2="-8.5999" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="UC3C0512C">
<pin name="PA00" x="-38.1" y="60.96" length="middle" rot="R270"/>
<pin name="PA01" x="-35.56" y="60.96" length="middle" rot="R270"/>
<pin name="PA02" x="-33.02" y="60.96" length="middle" rot="R270"/>
<pin name="PA03" x="-30.48" y="60.96" length="middle" rot="R270"/>
<pin name="PA04" x="-27.94" y="60.96" length="middle" rot="R270"/>
<pin name="PA05" x="-25.4" y="60.96" length="middle" rot="R270"/>
<pin name="PA06" x="-22.86" y="60.96" length="middle" rot="R270"/>
<pin name="PA07" x="-20.32" y="60.96" length="middle" rot="R270"/>
<pin name="PA08" x="-17.78" y="60.96" length="middle" rot="R270"/>
<pin name="PA09" x="-15.24" y="60.96" length="middle" rot="R270"/>
<pin name="PA10" x="-12.7" y="60.96" length="middle" rot="R270"/>
<pin name="PA11" x="-10.16" y="60.96" length="middle" rot="R270"/>
<pin name="PA12" x="-7.62" y="60.96" length="middle" rot="R270"/>
<pin name="PA13" x="-5.08" y="60.96" length="middle" rot="R270"/>
<pin name="PA14" x="-2.54" y="60.96" length="middle" rot="R270"/>
<pin name="PA15" x="0" y="60.96" length="middle" rot="R270"/>
<pin name="PA16" x="2.54" y="60.96" length="middle" rot="R270"/>
<pin name="ADCREFP" x="5.08" y="60.96" length="middle" rot="R270"/>
<pin name="ADCREFN" x="7.62" y="60.96" length="middle" rot="R270"/>
<pin name="PA19" x="10.16" y="60.96" length="middle" rot="R270"/>
<pin name="PA20" x="12.7" y="60.96" length="middle" rot="R270"/>
<pin name="PA21" x="15.24" y="60.96" length="middle" rot="R270"/>
<pin name="PA22" x="17.78" y="60.96" length="middle" rot="R270"/>
<pin name="PA23" x="20.32" y="60.96" length="middle" rot="R270"/>
<pin name="PA24" x="22.86" y="60.96" length="middle" rot="R270"/>
<pin name="PA25" x="25.4" y="60.96" length="middle" rot="R270"/>
<pin name="PA26" x="27.94" y="60.96" length="middle" rot="R270"/>
<pin name="PA27" x="30.48" y="60.96" length="middle" rot="R270"/>
<pin name="PA28" x="33.02" y="60.96" length="middle" rot="R270"/>
<pin name="PA29" x="35.56" y="60.96" length="middle" rot="R270"/>
<pin name="PB00" x="58.42" y="50.8" length="middle" rot="R180"/>
<pin name="PB01" x="58.42" y="48.26" length="middle" rot="R180"/>
<pin name="PB02" x="58.42" y="45.72" length="middle" rot="R180"/>
<pin name="PB03" x="58.42" y="43.18" length="middle" rot="R180"/>
<pin name="PB04" x="58.42" y="40.64" length="middle" rot="R180"/>
<pin name="PB05" x="58.42" y="38.1" length="middle" rot="R180"/>
<pin name="PB06" x="58.42" y="35.56" length="middle" rot="R180"/>
<pin name="PB07" x="58.42" y="33.02" length="middle" rot="R180"/>
<pin name="PB08" x="58.42" y="30.48" length="middle" rot="R180"/>
<pin name="PB09" x="58.42" y="27.94" length="middle" rot="R180"/>
<pin name="PB10" x="58.42" y="25.4" length="middle" rot="R180"/>
<pin name="PB11" x="58.42" y="22.86" length="middle" rot="R180"/>
<pin name="PB12" x="58.42" y="20.32" length="middle" rot="R180"/>
<pin name="PB13" x="58.42" y="17.78" length="middle" rot="R180"/>
<pin name="PB14" x="58.42" y="15.24" length="middle" rot="R180"/>
<pin name="PB15" x="58.42" y="12.7" length="middle" rot="R180"/>
<pin name="PB16" x="58.42" y="10.16" length="middle" rot="R180"/>
<pin name="PB17" x="58.42" y="7.62" length="middle" rot="R180"/>
<pin name="PB18" x="58.42" y="5.08" length="middle" rot="R180"/>
<pin name="PB19" x="58.42" y="2.54" length="middle" rot="R180"/>
<pin name="PB20" x="58.42" y="0" length="middle" rot="R180"/>
<pin name="PB21" x="58.42" y="-2.54" length="middle" rot="R180"/>
<pin name="PB22" x="58.42" y="-5.08" length="middle" rot="R180"/>
<pin name="PB23" x="58.42" y="-7.62" length="middle" rot="R180"/>
<pin name="PB24" x="58.42" y="-10.16" length="middle" rot="R180"/>
<pin name="PB25" x="58.42" y="-12.7" length="middle" rot="R180"/>
<pin name="PB26" x="58.42" y="-15.24" length="middle" rot="R180"/>
<pin name="PB27" x="58.42" y="-17.78" length="middle" rot="R180"/>
<pin name="PB28" x="58.42" y="-20.32" length="middle" rot="R180"/>
<pin name="PB29" x="58.42" y="-22.86" length="middle" rot="R180"/>
<pin name="PB30" x="58.42" y="-25.4" length="middle" rot="R180"/>
<pin name="PB31" x="58.42" y="-27.94" length="middle" rot="R180"/>
<pin name="PC00" x="40.64" y="-63.5" length="middle" rot="R90"/>
<pin name="PC01" x="38.1" y="-63.5" length="middle" rot="R90"/>
<pin name="PC02" x="35.56" y="-63.5" length="middle" rot="R90"/>
<pin name="PC03" x="33.02" y="-63.5" length="middle" rot="R90"/>
<pin name="PC04" x="30.48" y="-63.5" length="middle" rot="R90"/>
<pin name="PC05" x="27.94" y="-63.5" length="middle" rot="R90"/>
<pin name="PC06" x="25.4" y="-63.5" length="middle" rot="R90"/>
<pin name="PC07" x="22.86" y="-63.5" length="middle" rot="R90"/>
<pin name="PC08" x="20.32" y="-63.5" length="middle" rot="R90"/>
<pin name="PC09" x="17.78" y="-63.5" length="middle" rot="R90"/>
<pin name="PC10" x="15.24" y="-63.5" length="middle" rot="R90"/>
<pin name="PC11" x="12.7" y="-63.5" length="middle" rot="R90"/>
<pin name="PC12" x="10.16" y="-63.5" length="middle" rot="R90"/>
<pin name="PC13" x="7.62" y="-63.5" length="middle" rot="R90"/>
<pin name="PC14" x="5.08" y="-63.5" length="middle" rot="R90"/>
<pin name="PC15" x="2.54" y="-63.5" length="middle" rot="R90"/>
<pin name="PC16" x="0" y="-63.5" length="middle" rot="R90"/>
<pin name="PC17" x="-2.54" y="-63.5" length="middle" rot="R90"/>
<pin name="PC18" x="-5.08" y="-63.5" length="middle" rot="R90"/>
<pin name="PC19" x="-7.62" y="-63.5" length="middle" rot="R90"/>
<pin name="PC20" x="-10.16" y="-63.5" length="middle" rot="R90"/>
<pin name="PC21" x="-12.7" y="-63.5" length="middle" rot="R90"/>
<pin name="PC22" x="-15.24" y="-63.5" length="middle" rot="R90"/>
<pin name="PC23" x="-17.78" y="-63.5" length="middle" rot="R90"/>
<pin name="PC24" x="-20.32" y="-63.5" length="middle" rot="R90"/>
<pin name="PC25" x="-22.86" y="-63.5" length="middle" rot="R90"/>
<pin name="PC26" x="-25.4" y="-63.5" length="middle" rot="R90"/>
<pin name="PC27" x="-27.94" y="-63.5" length="middle" rot="R90"/>
<pin name="PC28" x="-30.48" y="-63.5" length="middle" rot="R90"/>
<pin name="PC29" x="-33.02" y="-63.5" length="middle" rot="R90"/>
<pin name="PC30" x="-35.56" y="-63.5" length="middle" rot="R90"/>
<pin name="PC31" x="-38.1" y="-63.5" length="middle" rot="R90"/>
<pin name="PD00" x="-55.88" y="-50.8" length="middle"/>
<pin name="PD01" x="-55.88" y="-48.26" length="middle"/>
<pin name="PD02" x="-55.88" y="-45.72" length="middle"/>
<pin name="PD03" x="-55.88" y="-43.18" length="middle"/>
<pin name="PD04" x="-55.88" y="-40.64" length="middle"/>
<pin name="PD05" x="-55.88" y="-38.1" length="middle"/>
<pin name="PD06" x="-55.88" y="-35.56" length="middle"/>
<pin name="PD07" x="-55.88" y="-33.02" length="middle"/>
<pin name="PD08" x="-55.88" y="-30.48" length="middle"/>
<pin name="PD09" x="-55.88" y="-27.94" length="middle"/>
<pin name="PD10" x="-55.88" y="-25.4" length="middle"/>
<pin name="PD11" x="-55.88" y="-22.86" length="middle"/>
<pin name="PD12" x="-55.88" y="-20.32" length="middle"/>
<pin name="PD13" x="-55.88" y="-17.78" length="middle"/>
<pin name="PD14" x="-55.88" y="-15.24" length="middle"/>
<pin name="PD15" x="-55.88" y="-12.7" length="middle"/>
<pin name="PD16" x="-55.88" y="-10.16" length="middle"/>
<pin name="PD17" x="-55.88" y="-7.62" length="middle"/>
<pin name="PD18" x="-55.88" y="-5.08" length="middle"/>
<pin name="PD19" x="-55.88" y="-2.54" length="middle"/>
<pin name="PD20" x="-55.88" y="0" length="middle"/>
<pin name="PD21" x="-55.88" y="2.54" length="middle"/>
<pin name="PD22" x="-55.88" y="5.08" length="middle"/>
<pin name="PD23" x="-55.88" y="7.62" length="middle"/>
<pin name="PD24" x="-55.88" y="10.16" length="middle"/>
<pin name="PD25" x="-55.88" y="12.7" length="middle"/>
<pin name="PD26" x="-55.88" y="15.24" length="middle"/>
<pin name="PD27" x="-55.88" y="17.78" length="middle"/>
<pin name="PD28" x="-55.88" y="20.32" length="middle"/>
<pin name="PD29" x="-55.88" y="22.86" length="middle"/>
<pin name="PD30" x="-55.88" y="25.4" length="middle"/>
<pin name="VDDIO1" x="-55.88" y="48.26" length="middle" direction="pwr"/>
<pin name="GNDIO1" x="58.42" y="-33.02" length="middle" direction="pwr" rot="R180"/>
<pin name="VDDIO2" x="-55.88" y="45.72" length="middle" direction="pwr"/>
<pin name="GNDIO2" x="58.42" y="-35.56" length="middle" direction="pwr" rot="R180"/>
<pin name="VDDIO3" x="-55.88" y="43.18" length="middle" direction="pwr"/>
<pin name="GNDIO3" x="58.42" y="-38.1" length="middle" direction="pwr" rot="R180"/>
<pin name="VDDIO4" x="-55.88" y="40.64" length="middle" direction="pwr"/>
<pin name="GNDIO4" x="58.42" y="-40.64" length="middle" direction="pwr" rot="R180"/>
<pin name="VDDCORE" x="-55.88" y="38.1" length="middle" direction="pwr"/>
<pin name="GNDCORE" x="58.42" y="-43.18" length="middle" direction="pwr" rot="R180"/>
<pin name="VDDIN_33" x="-55.88" y="35.56" length="middle" direction="pwr"/>
<pin name="VDDIN_5" x="-55.88" y="33.02" length="middle" direction="pwr"/>
<pin name="GNDPLL" x="58.42" y="-45.72" length="middle" direction="pwr" rot="R180"/>
<pin name="VBUS" x="50.8" y="-63.5" length="middle" direction="pwr" rot="R90"/>
<pin name="DP" x="48.26" y="-63.5" length="middle" rot="R90"/>
<pin name="DM" x="45.72" y="-63.5" length="middle" rot="R90"/>
<pin name="VDDANA" x="-55.88" y="30.48" length="middle" direction="pwr"/>
<pin name="GNDANA" x="58.42" y="-48.26" length="middle" direction="pwr" rot="R180"/>
<pin name="RESET_N" x="40.64" y="60.96" length="middle" direction="in" rot="R270"/>
<wire x1="-50.8" y1="-50.8" x2="-50.8" y2="55.88" width="0.254" layer="94"/>
<wire x1="-50.8" y1="55.88" x2="53.34" y2="55.88" width="0.254" layer="94"/>
<wire x1="53.34" y1="55.88" x2="53.34" y2="-58.42" width="0.254" layer="94"/>
<wire x1="53.34" y1="-58.42" x2="-50.8" y2="-58.42" width="0.254" layer="94"/>
<wire x1="-50.8" y1="-58.42" x2="-50.8" y2="-50.8" width="0.254" layer="94"/>
<text x="-50.8" y="58.42" size="1.27" layer="95">&gt;Name</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="UC3C" prefix="IC">
<description>AT32UC3C0512C Schematic and Footprint</description>
<gates>
<gate name="G$1" symbol="UC3C0512C" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TQFP144">
<connects>
<connect gate="G$1" pin="ADCREFN" pad="35"/>
<connect gate="G$1" pin="ADCREFP" pad="34"/>
<connect gate="G$1" pin="DM" pad="50"/>
<connect gate="G$1" pin="DP" pad="51"/>
<connect gate="G$1" pin="GNDANA" pad="37"/>
<connect gate="G$1" pin="GNDCORE" pad="56"/>
<connect gate="G$1" pin="GNDIO1" pad="6"/>
<connect gate="G$1" pin="GNDIO2" pad="76"/>
<connect gate="G$1" pin="GNDIO3" pad="104"/>
<connect gate="G$1" pin="GNDIO4" pad="119"/>
<connect gate="G$1" pin="GNDPLL" pad="52"/>
<connect gate="G$1" pin="PA00" pad="1"/>
<connect gate="G$1" pin="PA01" pad="2"/>
<connect gate="G$1" pin="PA02" pad="3"/>
<connect gate="G$1" pin="PA03" pad="4"/>
<connect gate="G$1" pin="PA04" pad="21"/>
<connect gate="G$1" pin="PA05" pad="22"/>
<connect gate="G$1" pin="PA06" pad="23"/>
<connect gate="G$1" pin="PA07" pad="24"/>
<connect gate="G$1" pin="PA08" pad="25"/>
<connect gate="G$1" pin="PA09" pad="26"/>
<connect gate="G$1" pin="PA10" pad="27"/>
<connect gate="G$1" pin="PA11" pad="28"/>
<connect gate="G$1" pin="PA12" pad="29"/>
<connect gate="G$1" pin="PA13" pad="30"/>
<connect gate="G$1" pin="PA14" pad="31"/>
<connect gate="G$1" pin="PA15" pad="32"/>
<connect gate="G$1" pin="PA16" pad="33"/>
<connect gate="G$1" pin="PA19" pad="36"/>
<connect gate="G$1" pin="PA20" pad="39"/>
<connect gate="G$1" pin="PA21" pad="40"/>
<connect gate="G$1" pin="PA22" pad="41"/>
<connect gate="G$1" pin="PA23" pad="42"/>
<connect gate="G$1" pin="PA24" pad="43"/>
<connect gate="G$1" pin="PA25" pad="44"/>
<connect gate="G$1" pin="PA26" pad="45"/>
<connect gate="G$1" pin="PA27" pad="46"/>
<connect gate="G$1" pin="PA28" pad="47"/>
<connect gate="G$1" pin="PA29" pad="48"/>
<connect gate="G$1" pin="PB00" pad="140"/>
<connect gate="G$1" pin="PB01" pad="141"/>
<connect gate="G$1" pin="PB02" pad="143"/>
<connect gate="G$1" pin="PB03" pad="144"/>
<connect gate="G$1" pin="PB04" pad="7"/>
<connect gate="G$1" pin="PB05" pad="8"/>
<connect gate="G$1" pin="PB06" pad="9"/>
<connect gate="G$1" pin="PB07" pad="10"/>
<connect gate="G$1" pin="PB08" pad="11"/>
<connect gate="G$1" pin="PB09" pad="12"/>
<connect gate="G$1" pin="PB10" pad="13"/>
<connect gate="G$1" pin="PB11" pad="14"/>
<connect gate="G$1" pin="PB12" pad="15"/>
<connect gate="G$1" pin="PB13" pad="16"/>
<connect gate="G$1" pin="PB14" pad="17"/>
<connect gate="G$1" pin="PB15" pad="18"/>
<connect gate="G$1" pin="PB16" pad="19"/>
<connect gate="G$1" pin="PB17" pad="20"/>
<connect gate="G$1" pin="PB18" pad="57"/>
<connect gate="G$1" pin="PB19" pad="58"/>
<connect gate="G$1" pin="PB20" pad="59"/>
<connect gate="G$1" pin="PB21" pad="60"/>
<connect gate="G$1" pin="PB22" pad="61"/>
<connect gate="G$1" pin="PB23" pad="62"/>
<connect gate="G$1" pin="PB24" pad="63"/>
<connect gate="G$1" pin="PB25" pad="64"/>
<connect gate="G$1" pin="PB26" pad="65"/>
<connect gate="G$1" pin="PB27" pad="66"/>
<connect gate="G$1" pin="PB28" pad="67"/>
<connect gate="G$1" pin="PB29" pad="68"/>
<connect gate="G$1" pin="PB30" pad="69"/>
<connect gate="G$1" pin="PB31" pad="70"/>
<connect gate="G$1" pin="PC00" pad="71"/>
<connect gate="G$1" pin="PC01" pad="72"/>
<connect gate="G$1" pin="PC02" pad="73"/>
<connect gate="G$1" pin="PC03" pad="74"/>
<connect gate="G$1" pin="PC04" pad="77"/>
<connect gate="G$1" pin="PC05" pad="78"/>
<connect gate="G$1" pin="PC06" pad="79"/>
<connect gate="G$1" pin="PC07" pad="80"/>
<connect gate="G$1" pin="PC08" pad="81"/>
<connect gate="G$1" pin="PC09" pad="82"/>
<connect gate="G$1" pin="PC10" pad="83"/>
<connect gate="G$1" pin="PC11" pad="84"/>
<connect gate="G$1" pin="PC12" pad="85"/>
<connect gate="G$1" pin="PC13" pad="86"/>
<connect gate="G$1" pin="PC14" pad="87"/>
<connect gate="G$1" pin="PC15" pad="88"/>
<connect gate="G$1" pin="PC16" pad="89"/>
<connect gate="G$1" pin="PC17" pad="90"/>
<connect gate="G$1" pin="PC18" pad="91"/>
<connect gate="G$1" pin="PC19" pad="92"/>
<connect gate="G$1" pin="PC20" pad="93"/>
<connect gate="G$1" pin="PC21" pad="94"/>
<connect gate="G$1" pin="PC22" pad="95"/>
<connect gate="G$1" pin="PC23" pad="96"/>
<connect gate="G$1" pin="PC24" pad="97"/>
<connect gate="G$1" pin="PC25" pad="98"/>
<connect gate="G$1" pin="PC26" pad="99"/>
<connect gate="G$1" pin="PC27" pad="100"/>
<connect gate="G$1" pin="PC28" pad="101"/>
<connect gate="G$1" pin="PC29" pad="102"/>
<connect gate="G$1" pin="PC30" pad="105"/>
<connect gate="G$1" pin="PC31" pad="106"/>
<connect gate="G$1" pin="PD00" pad="107"/>
<connect gate="G$1" pin="PD01" pad="108"/>
<connect gate="G$1" pin="PD02" pad="109"/>
<connect gate="G$1" pin="PD03" pad="110"/>
<connect gate="G$1" pin="PD04" pad="111"/>
<connect gate="G$1" pin="PD05" pad="112"/>
<connect gate="G$1" pin="PD06" pad="113"/>
<connect gate="G$1" pin="PD07" pad="114"/>
<connect gate="G$1" pin="PD08" pad="115"/>
<connect gate="G$1" pin="PD09" pad="116"/>
<connect gate="G$1" pin="PD10" pad="117"/>
<connect gate="G$1" pin="PD11" pad="120"/>
<connect gate="G$1" pin="PD12" pad="121"/>
<connect gate="G$1" pin="PD13" pad="122"/>
<connect gate="G$1" pin="PD14" pad="123"/>
<connect gate="G$1" pin="PD15" pad="124"/>
<connect gate="G$1" pin="PD16" pad="125"/>
<connect gate="G$1" pin="PD17" pad="126"/>
<connect gate="G$1" pin="PD18" pad="127"/>
<connect gate="G$1" pin="PD19" pad="128"/>
<connect gate="G$1" pin="PD20" pad="129"/>
<connect gate="G$1" pin="PD21" pad="130"/>
<connect gate="G$1" pin="PD22" pad="131"/>
<connect gate="G$1" pin="PD23" pad="132"/>
<connect gate="G$1" pin="PD24" pad="133"/>
<connect gate="G$1" pin="PD25" pad="134"/>
<connect gate="G$1" pin="PD26" pad="135"/>
<connect gate="G$1" pin="PD27" pad="136"/>
<connect gate="G$1" pin="PD28" pad="137"/>
<connect gate="G$1" pin="PD29" pad="138"/>
<connect gate="G$1" pin="PD30" pad="139"/>
<connect gate="G$1" pin="RESET_N" pad="142"/>
<connect gate="G$1" pin="VBUS" pad="49"/>
<connect gate="G$1" pin="VDDANA" pad="38"/>
<connect gate="G$1" pin="VDDCORE" pad="55"/>
<connect gate="G$1" pin="VDDIN_33" pad="54"/>
<connect gate="G$1" pin="VDDIN_5" pad="53"/>
<connect gate="G$1" pin="VDDIO1" pad="5"/>
<connect gate="G$1" pin="VDDIO2" pad="75"/>
<connect gate="G$1" pin="VDDIO3" pad="103"/>
<connect gate="G$1" pin="VDDIO4" pad="118"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Headers">
<packages>
<package name="2BY5">
<pad name="5" x="-1.27" y="0" drill="0.8"/>
<pad name="6" x="1.27" y="0" drill="0.8"/>
<pad name="4" x="1.27" y="2.54" drill="0.8"/>
<pad name="2" x="1.27" y="5.08" drill="0.8"/>
<pad name="1" x="-1.27" y="5.08" drill="0.8"/>
<pad name="3" x="-1.27" y="2.54" drill="0.8"/>
<pad name="7" x="-1.27" y="-2.54" drill="0.8"/>
<pad name="9" x="-1.27" y="-5.08" drill="0.8"/>
<pad name="10" x="1.27" y="-5.08" drill="0.8"/>
<pad name="8" x="1.27" y="-2.54" drill="0.8"/>
<wire x1="-2.54" y1="6.35" x2="2.54" y2="6.35" width="0.127" layer="21"/>
<wire x1="2.54" y1="6.35" x2="2.54" y2="-6.35" width="0.127" layer="21"/>
<wire x1="2.54" y1="-6.35" x2="-2.54" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-6.35" x2="-2.54" y2="6.35" width="0.127" layer="21"/>
<text x="2.54" y="7.62" size="1.27" layer="25" rot="R180">&gt;Name</text>
</package>
</packages>
<symbols>
<symbol name="JTAG">
<pin name="TCK" x="12.7" y="2.54" length="middle" rot="R180"/>
<pin name="TDI" x="12.7" y="0" length="middle" rot="R180"/>
<pin name="TDO" x="12.7" y="-2.54" length="middle" rot="R180"/>
<pin name="TMS" x="12.7" y="-5.08" length="middle" rot="R180"/>
<pin name="VREF" x="-12.7" y="2.54" length="middle"/>
<pin name="GND" x="-12.7" y="-2.54" length="middle"/>
<pin name="GND2" x="-12.7" y="-5.08" length="middle"/>
<wire x1="-7.62" y1="-7.62" x2="-7.62" y2="5.08" width="0.254" layer="94"/>
<wire x1="-7.62" y1="5.08" x2="7.62" y2="5.08" width="0.254" layer="94"/>
<wire x1="7.62" y1="5.08" x2="7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="7.62" y1="-7.62" x2="-7.62" y2="-7.62" width="0.254" layer="94"/>
<text x="-7.62" y="5.08" size="1.778" layer="95">&gt;Name</text>
<text x="-7.62" y="-10.16" size="1.778" layer="96">&gt;Value</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="JTAG" prefix="J" uservalue="yes">
<description>JTAG Header</description>
<gates>
<gate name="G$1" symbol="JTAG" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2BY5">
<connects>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="GND2" pad="10"/>
<connect gate="G$1" pin="TCK" pad="1"/>
<connect gate="G$1" pin="TDI" pad="9"/>
<connect gate="G$1" pin="TDO" pad="3"/>
<connect gate="G$1" pin="TMS" pad="5"/>
<connect gate="G$1" pin="VREF" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="+3V3">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+3V3" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="+3V3" prefix="+3V3">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+3V3" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
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
<part name="IC1" library="Atmel_MCUs" deviceset="UC3C" device=""/>
<part name="J1" library="Headers" deviceset="JTAG" device=""/>
<part name="+3V1" library="supply1" deviceset="+3V3" device=""/>
<part name="+3V2" library="supply1" deviceset="+3V3" device=""/>
<part name="GND1" library="supply1" deviceset="GND" device=""/>
<part name="GND2" library="supply1" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="IC1" gate="G$1" x="50.8" y="58.42"/>
<instance part="J1" gate="G$1" x="233.68" y="134.62"/>
<instance part="+3V1" gate="G$1" x="218.44" y="142.24"/>
<instance part="+3V2" gate="G$1" x="-10.16" y="111.76"/>
<instance part="GND1" gate="1" x="114.3" y="7.62"/>
<instance part="GND2" gate="1" x="218.44" y="127"/>
</instances>
<busses>
<bus name="PA[0..29]">
<segment>
<wire x1="12.7" y1="121.92" x2="86.36" y2="121.92" width="0.762" layer="92"/>
<label x="88.9" y="124.46" size="1.778" layer="95" rot="R90"/>
<wire x1="86.36" y1="121.92" x2="88.9" y2="124.46" width="0.762" layer="92"/>
</segment>
</bus>
<bus name="PB[0..31]">
<segment>
<wire x1="111.76" y1="109.22" x2="111.76" y2="30.48" width="0.762" layer="92"/>
<wire x1="111.76" y1="30.48" x2="114.3" y2="27.94" width="0.762" layer="92"/>
<label x="114.3" y="27.94" size="1.778" layer="95"/>
</segment>
</bus>
<bus name="PD[0..30]">
<segment>
<wire x1="-7.62" y1="83.82" x2="-7.62" y2="7.62" width="0.762" layer="92"/>
<wire x1="-7.62" y1="7.62" x2="-10.16" y2="5.08" width="0.762" layer="92"/>
<label x="-20.32" y="5.08" size="1.778" layer="95"/>
</segment>
</bus>
<bus name="PC[0..31]">
<segment>
<wire x1="91.44" y1="-7.62" x2="12.7" y2="-7.62" width="0.762" layer="92"/>
<wire x1="12.7" y1="-7.62" x2="10.16" y2="-10.16" width="0.762" layer="92"/>
<label x="0" y="-12.7" size="1.778" layer="95"/>
</segment>
</bus>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="GND"/>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="220.98" y1="132.08" x2="218.44" y2="132.08" width="0.1524" layer="91"/>
<wire x1="218.44" y1="132.08" x2="218.44" y2="129.54" width="0.1524" layer="91"/>
<pinref part="J1" gate="G$1" pin="GND2"/>
<wire x1="220.98" y1="129.54" x2="218.44" y2="129.54" width="0.1524" layer="91"/>
<junction x="218.44" y="129.54"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="GNDIO1"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="109.22" y1="25.4" x2="114.3" y2="25.4" width="0.1524" layer="91"/>
<wire x1="114.3" y1="25.4" x2="114.3" y2="22.86" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="GNDANA"/>
<wire x1="114.3" y1="22.86" x2="114.3" y2="20.32" width="0.1524" layer="91"/>
<wire x1="114.3" y1="20.32" x2="114.3" y2="17.78" width="0.1524" layer="91"/>
<wire x1="114.3" y1="17.78" x2="114.3" y2="15.24" width="0.1524" layer="91"/>
<wire x1="114.3" y1="15.24" x2="114.3" y2="12.7" width="0.1524" layer="91"/>
<wire x1="114.3" y1="12.7" x2="114.3" y2="10.16" width="0.1524" layer="91"/>
<wire x1="109.22" y1="10.16" x2="114.3" y2="10.16" width="0.1524" layer="91"/>
<junction x="114.3" y="10.16"/>
<pinref part="IC1" gate="G$1" pin="GNDPLL"/>
<wire x1="109.22" y1="12.7" x2="114.3" y2="12.7" width="0.1524" layer="91"/>
<junction x="114.3" y="12.7"/>
<pinref part="IC1" gate="G$1" pin="GNDCORE"/>
<wire x1="109.22" y1="15.24" x2="114.3" y2="15.24" width="0.1524" layer="91"/>
<junction x="114.3" y="15.24"/>
<pinref part="IC1" gate="G$1" pin="GNDIO4"/>
<wire x1="109.22" y1="17.78" x2="114.3" y2="17.78" width="0.1524" layer="91"/>
<junction x="114.3" y="17.78"/>
<pinref part="IC1" gate="G$1" pin="GNDIO3"/>
<wire x1="109.22" y1="20.32" x2="114.3" y2="20.32" width="0.1524" layer="91"/>
<junction x="114.3" y="20.32"/>
<pinref part="IC1" gate="G$1" pin="GNDIO2"/>
<wire x1="109.22" y1="22.86" x2="114.3" y2="22.86" width="0.1524" layer="91"/>
<junction x="114.3" y="22.86"/>
</segment>
</net>
<net name="+3V3" class="0">
<segment>
<pinref part="+3V1" gate="G$1" pin="+3V3"/>
<pinref part="J1" gate="G$1" pin="VREF"/>
<wire x1="218.44" y1="139.7" x2="218.44" y2="137.16" width="0.1524" layer="91"/>
<wire x1="218.44" y1="137.16" x2="220.98" y2="137.16" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="+3V2" gate="G$1" pin="+3V3"/>
<pinref part="IC1" gate="G$1" pin="VDDANA"/>
<wire x1="-10.16" y1="109.22" x2="-10.16" y2="106.68" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="106.68" x2="-10.16" y2="104.14" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="104.14" x2="-10.16" y2="101.6" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="101.6" x2="-10.16" y2="99.06" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="99.06" x2="-10.16" y2="93.98" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="93.98" x2="-10.16" y2="88.9" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="88.9" x2="-5.08" y2="88.9" width="0.1524" layer="91"/>
<pinref part="IC1" gate="G$1" pin="VDDIN_33"/>
<wire x1="-10.16" y1="93.98" x2="-5.08" y2="93.98" width="0.1524" layer="91"/>
<junction x="-10.16" y="93.98"/>
<pinref part="IC1" gate="G$1" pin="VDDIO4"/>
<wire x1="-5.08" y1="99.06" x2="-10.16" y2="99.06" width="0.1524" layer="91"/>
<junction x="-10.16" y="99.06"/>
<pinref part="IC1" gate="G$1" pin="VDDIO3"/>
<wire x1="-5.08" y1="101.6" x2="-10.16" y2="101.6" width="0.1524" layer="91"/>
<junction x="-10.16" y="101.6"/>
<pinref part="IC1" gate="G$1" pin="VDDIO2"/>
<wire x1="-5.08" y1="104.14" x2="-10.16" y2="104.14" width="0.1524" layer="91"/>
<junction x="-10.16" y="104.14"/>
<pinref part="IC1" gate="G$1" pin="VDDIO1"/>
<wire x1="-5.08" y1="106.68" x2="-10.16" y2="106.68" width="0.1524" layer="91"/>
<junction x="-10.16" y="106.68"/>
</segment>
</net>
<net name="TCK" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="TCK"/>
<wire x1="246.38" y1="137.16" x2="248.92" y2="137.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="TDI" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="TDI"/>
<wire x1="246.38" y1="134.62" x2="248.92" y2="134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="TDO" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="TDO"/>
<wire x1="246.38" y1="132.08" x2="248.92" y2="132.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="TMS" class="0">
<segment>
<pinref part="J1" gate="G$1" pin="TMS"/>
<wire x1="246.38" y1="129.54" x2="248.92" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA0" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA00"/>
<wire x1="12.7" y1="119.38" x2="12.7" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA01"/>
<wire x1="15.24" y1="119.38" x2="15.24" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA02"/>
<wire x1="17.78" y1="119.38" x2="17.78" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA03"/>
<wire x1="20.32" y1="119.38" x2="20.32" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA4" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA04"/>
<wire x1="22.86" y1="119.38" x2="22.86" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA5" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA05"/>
<wire x1="25.4" y1="119.38" x2="25.4" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA6" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA06"/>
<wire x1="27.94" y1="119.38" x2="27.94" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA7" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA07"/>
<wire x1="30.48" y1="119.38" x2="30.48" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA8" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA08"/>
<wire x1="33.02" y1="119.38" x2="33.02" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA9" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA09"/>
<wire x1="35.56" y1="119.38" x2="35.56" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA10" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA10"/>
<wire x1="38.1" y1="119.38" x2="38.1" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA11" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA11"/>
<wire x1="40.64" y1="119.38" x2="40.64" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA12" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA12"/>
<wire x1="43.18" y1="119.38" x2="43.18" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA13" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA13"/>
<wire x1="45.72" y1="119.38" x2="45.72" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA14" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA14"/>
<wire x1="48.26" y1="119.38" x2="48.26" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA15" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA15"/>
<wire x1="50.8" y1="119.38" x2="50.8" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA16" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA16"/>
<wire x1="53.34" y1="119.38" x2="53.34" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA19" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA19"/>
<wire x1="60.96" y1="119.38" x2="60.96" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA20" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA20"/>
<wire x1="63.5" y1="119.38" x2="63.5" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA21" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA21"/>
<wire x1="66.04" y1="119.38" x2="66.04" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA22" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA22"/>
<wire x1="68.58" y1="119.38" x2="68.58" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA23" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA23"/>
<wire x1="71.12" y1="119.38" x2="71.12" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA24" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA24"/>
<wire x1="73.66" y1="119.38" x2="73.66" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA25" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA25"/>
<wire x1="76.2" y1="119.38" x2="76.2" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA26" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA26"/>
<wire x1="78.74" y1="119.38" x2="78.74" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA27" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA27"/>
<wire x1="81.28" y1="119.38" x2="81.28" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA28" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA28"/>
<wire x1="83.82" y1="119.38" x2="83.82" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PA29" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PA29"/>
<wire x1="86.36" y1="119.38" x2="86.36" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB0" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB00"/>
<wire x1="111.76" y1="109.22" x2="109.22" y2="109.22" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB01"/>
<wire x1="111.76" y1="106.68" x2="109.22" y2="106.68" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB02"/>
<wire x1="111.76" y1="104.14" x2="109.22" y2="104.14" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB03"/>
<wire x1="111.76" y1="101.6" x2="109.22" y2="101.6" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB4" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB04"/>
<wire x1="111.76" y1="99.06" x2="109.22" y2="99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB5" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB05"/>
<wire x1="111.76" y1="96.52" x2="109.22" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB6" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB06"/>
<wire x1="109.22" y1="93.98" x2="111.76" y2="93.98" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB7" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB07"/>
<wire x1="109.22" y1="91.44" x2="111.76" y2="91.44" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB8" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB08"/>
<wire x1="109.22" y1="88.9" x2="111.76" y2="88.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB9" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB09"/>
<wire x1="109.22" y1="86.36" x2="111.76" y2="86.36" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB10" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB10"/>
<wire x1="109.22" y1="83.82" x2="111.76" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB11" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB11"/>
<wire x1="109.22" y1="81.28" x2="111.76" y2="81.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB12" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB12"/>
<wire x1="109.22" y1="78.74" x2="111.76" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB13" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB13"/>
<wire x1="109.22" y1="76.2" x2="111.76" y2="76.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB14" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB14"/>
<wire x1="109.22" y1="73.66" x2="111.76" y2="73.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB15" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB15"/>
<wire x1="109.22" y1="71.12" x2="111.76" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB16" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB16"/>
<wire x1="109.22" y1="68.58" x2="111.76" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB17" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB17"/>
<wire x1="109.22" y1="66.04" x2="111.76" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB18" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB18"/>
<wire x1="109.22" y1="63.5" x2="111.76" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB19" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB19"/>
<wire x1="109.22" y1="60.96" x2="111.76" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB20" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB20"/>
<wire x1="109.22" y1="58.42" x2="111.76" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB21" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB21"/>
<wire x1="109.22" y1="55.88" x2="111.76" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB22" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB22"/>
<wire x1="109.22" y1="53.34" x2="111.76" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB23" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB23"/>
<wire x1="109.22" y1="50.8" x2="111.76" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB24" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB24"/>
<wire x1="109.22" y1="48.26" x2="111.76" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB25" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB25"/>
<wire x1="109.22" y1="45.72" x2="111.76" y2="45.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB26" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB26"/>
<wire x1="109.22" y1="43.18" x2="111.76" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB27" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB27"/>
<wire x1="109.22" y1="40.64" x2="111.76" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB28" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB28"/>
<wire x1="109.22" y1="38.1" x2="111.76" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB29" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB29"/>
<wire x1="109.22" y1="35.56" x2="111.76" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB30" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB30"/>
<wire x1="109.22" y1="33.02" x2="111.76" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PB31" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PB31"/>
<wire x1="109.22" y1="30.48" x2="111.76" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD30" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD30"/>
<wire x1="-5.08" y1="83.82" x2="-7.62" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD29" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD29"/>
<wire x1="-5.08" y1="81.28" x2="-7.62" y2="81.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD28" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD28"/>
<wire x1="-5.08" y1="78.74" x2="-7.62" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD27" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD27"/>
<wire x1="-5.08" y1="76.2" x2="-7.62" y2="76.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD26" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD26"/>
<wire x1="-5.08" y1="73.66" x2="-7.62" y2="73.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD25" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD25"/>
<wire x1="-5.08" y1="71.12" x2="-7.62" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD24" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD24"/>
<wire x1="-5.08" y1="68.58" x2="-7.62" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD23" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD23"/>
<wire x1="-5.08" y1="66.04" x2="-7.62" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD22" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD22"/>
<wire x1="-5.08" y1="63.5" x2="-7.62" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD21" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD21"/>
<wire x1="-5.08" y1="60.96" x2="-7.62" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD20" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD20"/>
<wire x1="-5.08" y1="58.42" x2="-7.62" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD19" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD19"/>
<wire x1="-5.08" y1="55.88" x2="-7.62" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD18" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD18"/>
<wire x1="-5.08" y1="53.34" x2="-7.62" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD17" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD17"/>
<wire x1="-5.08" y1="50.8" x2="-7.62" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD16" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD16"/>
<wire x1="-5.08" y1="48.26" x2="-7.62" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD15" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD15"/>
<wire x1="-5.08" y1="45.72" x2="-7.62" y2="45.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD14" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD14"/>
<wire x1="-5.08" y1="43.18" x2="-7.62" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD13" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD13"/>
<wire x1="-5.08" y1="40.64" x2="-7.62" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD12" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD12"/>
<wire x1="-5.08" y1="38.1" x2="-7.62" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD11" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD11"/>
<wire x1="-5.08" y1="35.56" x2="-7.62" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD10" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD10"/>
<wire x1="-5.08" y1="33.02" x2="-7.62" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD9" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD09"/>
<wire x1="-5.08" y1="30.48" x2="-7.62" y2="30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD8" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD08"/>
<wire x1="-5.08" y1="27.94" x2="-7.62" y2="27.94" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD7" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD07"/>
<wire x1="-5.08" y1="25.4" x2="-7.62" y2="25.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD6" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD06"/>
<wire x1="-5.08" y1="22.86" x2="-7.62" y2="22.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD5" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD05"/>
<wire x1="-5.08" y1="20.32" x2="-7.62" y2="20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD4" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD04"/>
<wire x1="-5.08" y1="17.78" x2="-7.62" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD03"/>
<wire x1="-5.08" y1="15.24" x2="-7.62" y2="15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD02"/>
<wire x1="-5.08" y1="12.7" x2="-7.62" y2="12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD01"/>
<wire x1="-5.08" y1="10.16" x2="-7.62" y2="10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PD0" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PD00"/>
<wire x1="-5.08" y1="7.62" x2="-7.62" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC31" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC31"/>
<wire x1="12.7" y1="-5.08" x2="12.7" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC30" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC30"/>
<wire x1="15.24" y1="-5.08" x2="15.24" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC29" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC29"/>
<wire x1="17.78" y1="-5.08" x2="17.78" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC28" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC28"/>
<wire x1="20.32" y1="-5.08" x2="20.32" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC27" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC27"/>
<wire x1="22.86" y1="-5.08" x2="22.86" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC26" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC26"/>
<wire x1="25.4" y1="-5.08" x2="25.4" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC25" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC25"/>
<wire x1="27.94" y1="-5.08" x2="27.94" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC24" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC24"/>
<wire x1="30.48" y1="-5.08" x2="30.48" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC23" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC23"/>
<wire x1="33.02" y1="-5.08" x2="33.02" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC22" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC22"/>
<wire x1="35.56" y1="-5.08" x2="35.56" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC21" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC21"/>
<wire x1="38.1" y1="-5.08" x2="38.1" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC20" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC20"/>
<wire x1="40.64" y1="-5.08" x2="40.64" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC19" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC19"/>
<wire x1="43.18" y1="-5.08" x2="43.18" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC18" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC18"/>
<wire x1="45.72" y1="-5.08" x2="45.72" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC17" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC17"/>
<wire x1="48.26" y1="-5.08" x2="48.26" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC16" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC16"/>
<wire x1="50.8" y1="-5.08" x2="50.8" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC15" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC15"/>
<wire x1="53.34" y1="-5.08" x2="53.34" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC14" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC14"/>
<wire x1="55.88" y1="-5.08" x2="55.88" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC13" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC13"/>
<wire x1="58.42" y1="-5.08" x2="58.42" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC12" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC12"/>
<wire x1="60.96" y1="-5.08" x2="60.96" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC11" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC11"/>
<wire x1="63.5" y1="-5.08" x2="63.5" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC10" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC10"/>
<wire x1="66.04" y1="-5.08" x2="66.04" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC9" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC09"/>
<wire x1="68.58" y1="-5.08" x2="68.58" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC8" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC08"/>
<wire x1="71.12" y1="-5.08" x2="71.12" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC7" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC07"/>
<wire x1="73.66" y1="-5.08" x2="73.66" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC6" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC06"/>
<wire x1="76.2" y1="-5.08" x2="76.2" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC5" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC05"/>
<wire x1="78.74" y1="-5.08" x2="78.74" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC4" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC04"/>
<wire x1="81.28" y1="-5.08" x2="81.28" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC3" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC03"/>
<wire x1="83.82" y1="-5.08" x2="83.82" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC2" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC02"/>
<wire x1="86.36" y1="-5.08" x2="86.36" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC1" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC01"/>
<wire x1="88.9" y1="-5.08" x2="88.9" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PC0" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="PC00"/>
<wire x1="91.44" y1="-5.08" x2="91.44" y2="-7.62" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
