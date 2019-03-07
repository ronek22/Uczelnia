<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <SOLAR_SYSTEM>
   <PLANETS>
   <xsl:for-each select="SOLAR_SYSTEM/PLANETS/PLANET[DENSITY>3]">
   <xsl:sort select="DENSITY"/>
   <PLANET>
     <NAME><xsl:value-of select="NAME"/></NAME>
     <DENSITY><xsl:value-of select="DENSITY"/></DENSITY>
   </PLANET>
   </xsl:for-each>
 </PLANETS>

</SOLAR_SYSTEM>

</xsl:template>

</xsl:stylesheet>
