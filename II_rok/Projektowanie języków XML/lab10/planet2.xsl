<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/"/>
  <SOLAR_SYSTEM>
    <PLANETS>
	<xsl:for-each select="SOLAR_SYSTEM/PLANETS/PLANET[DENSINITY>3]">
    <PLANET>
	<NAME><xsl:value-of select="NAME"/></NAME>
  <DISTANCE></DISTANCE>
  <RADIUS UNITS="km"></RADIUS>
  <LENGTH_OF_YEAR></LENGTH_OF_YEAR>
  <DAY UNITS="days"></DAY>
  <MASS UNITS="(Earth=1)"></MASS>
  <DENSITY UNITS="gm/cm"></DENSITY>
</PLANET>
		</xsl:for-each>
  </PLANETS>

</xsl:template>

</xsl:stylesheet>
