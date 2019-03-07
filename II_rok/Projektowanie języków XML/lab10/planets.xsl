<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <body>
<head>
    <style> ol li u { padding-right: 5px; } </style>
  </head>
  <h2>Planety</h2>
	<ul>
		<xsl:for-each select="SOLAR_SYSTEM/PLANETS/PLANET">
		<li>
		  <font color="{@COLOR}"><xsl:value-of select="NAME"/></font>
		</li>
		</xsl:for-each>
	</ul>
  </body>
  </html>
</xsl:template>

</xsl:stylesheet>
