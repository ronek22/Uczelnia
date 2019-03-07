<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:ex="http://exslt.org/dates-and-times" extension-element-prefixes="ex">

    <xsl:output method="xml" version="1.0" encoding="utf-8" indent="yes" omit-xml-declaration="yes"/>

    <xsl:key name="rel" match="wypozyczalnia/samochody/samochod" use="nr-rej"/>

    <xsl:template match="/">
        <xsl:text disable-output-escaping="yes">&lt;!DOCTYPE html&gt;</xsl:text>
        <html>
            <head>
                <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
                <title>Projekt</title>
                <style>
                    @import url( 'https://fonts.googleapis.com/css?family=Lato');
                    @font-face {
                        font-family: 'Roboto';
                        font-style: normal;
                        font-weight: 400;
                        src: local('Roboto Regular'), local('Roboto-Regular'), url("http://themes.googleusercontent.com/static/fonts/roboto/v11/2UX7WLTfW3W8TclTUvlFyQ.woff") format('woff');
                    }
                    @font-face {
                        font-family: 'Roboto';
                        font-style: normal;
                        font-weight: 700;
                        src: local('Roboto Bold'), local('Roboto-Bold'), url("http://themes.googleusercontent.com/static/fonts/roboto/v11/d-6IYplOFocCacKzxwXSOD8E0i7KZn-EPnyo3HZu7kw.woff") format('woff');
                    }
                    @font-face {
                        font-family: 'Roboto';
                        font-style: italic;
                        font-weight: 400;
                        src: local('Roboto Italic'), local('Roboto-Italic'), url("http://themes.googleusercontent.com/static/fonts/roboto/v11/1pO9eUAp8pSF8VnRTP3xnvesZW2xOQ-xsNqO47m55DA.woff") format('woff');
                    }

                    h1 {
                        font-family: 'Lato';
                        font-size: 28px;
                        font-style: normal;
                        font-variant: normal;
                        font-weight: bold;
                        line-height: 66px;
                    }
                    h3 {
                        font-family: 'Lato';
                        font-size: 22px;
                        font-style: normal;
                        font-variant: normal;
                        font-weight: 700;
                        line-height: 15.4px;
                    }

                    h4 {
                        font-family: 'Lato';
                        font-size: 20px;
                        font-style: normal;
                        font-variant: normal;
                        font-weight: 700;
                        line-height: 15.4px;
                    }

                    p {
                        font-family: 'Roboto', sans-serif;
                        font-size: 15px;
                        line-height: 20px;
                    }

                    hr {

                        border: 0;
                        height: 0;
                        border-top: 1px solid rgba(0, 0, 0, 0.1);
                        border-bottom: 1px solid rgba(255, 255, 255, 0.3);

                    }

                    body {
                        background: #e2e1e0;
                        font-family: 'Roboto', sans-serif;
                        font-size: 15px;
                    }

                    .personphoto {
                        float: left;
                    }

                    .person {
                        width: 100%;
                        background: #fff;
                        border-radius: 2px;
                        display: inline-block;
                        margin: 1rem 1rem 1rem 50px;
                        padding: 1rem;
                        transition: all 0.3s cubic-bezier(.25,.8,.25,1);
                        box-shadow: 0 3px 6px rgba(0,0,0,0.16), 0 3px 6px rgba(0,0,0,0.23);
                    }

                    .person img {
                        margin-right: 0.5rem;
                        border: 1px solid rgba(0, 0, 0, 0.1);
                        float: left;
                        text-align: left;
                        width: 100%;
                        max-width: 120px;
                    }

                    .personpost {
                        margin-left: 140px;
                    }
                    .person:hover {
                        box-shadow: 0 14px 28px rgba(0,0,0,0.25), 0 10px 10px rgba(0,0,0,0.22);
                    }

                    .example {
                        list-style: none;
                        padding: 0.5rem;
                        margin: 0;
                        color: #fff;
                    }
                    .example li:nth-child(odd) {
                        background-color: #34495e;
                        padding: 0.5rem;
                    }
                    .example li:nth-child(even) {
                        background-color: #2c3e50;
                        padding: 0.5rem;
                    }

                    .wrapper {
                        width: 800px;
                        margin: 0 auto;
                    }

                </style>
            </head>
            <body>
                <div class="wrapper">
                    <h1>Wypożyczalnia samochodów</h1>

                    <xsl:apply-templates/>
                </div>
            </body>
        </html>
    </xsl:template>

    <xsl:template match="samochody"></xsl:template>

    <xsl:template match="osoba">
        <div class="person">
            <div class="personphoto">
                <img alt="zdjecie">

                    <xsl:attribute name="src">
                        <xsl:value-of select="zdjecie"/>
                    </xsl:attribute>
                </img>
            </div>
            <div class="personpost">
              <xsl:variable name="dobyear" select="substring((data-ur),1,4)" />
              <xsl:variable name="currentyear" select="ex:year()" />
                <xsl:variable name="Birthday" select="data-ur"/>
                <xsl:variable name="Age">
                            <xsl:value-of select="$currentyear - $dobyear"/>
                </xsl:variable>

                <h3><xsl:value-of select="imie"/>
                    <xsl:text> </xsl:text>

                    <xsl:value-of select="nazwisko"/></h3><hr/>
                <p>Data urodzenia: <xsl:value-of select="data-ur"/> ( <xsl:value-of select="$Age"/> lat )</p>
                <p>Nr dowodu:

                    <xsl:value-of select="nr-dowodu"/></p>

                <xsl:apply-templates select="adres"/>
                <hr/>
                <p>Login:

                    <xsl:value-of select="login"/></p>
                <p>Hasło:

                    <xsl:value-of select="hasło"/></p>
                <hr/>

                <xsl:choose>

                    <xsl:when test="@plec = 'm'">
                        <h4>Wypożyczył

                            <xsl:value-of select="count(wypozyczenie)"/>
                            samochod( y/ów )</h4>
                    </xsl:when>

                    <xsl:otherwise>
                        <h4>Wypożyczyła

                            <xsl:value-of select="count(wypozyczenie)"/>
                            samochod( y/ów )</h4>
                    </xsl:otherwise>
                </xsl:choose>

                <xsl:apply-templates select="wypozyczenie"/>
            </div>
        </div>
    </xsl:template>

    <xsl:template match="wypozyczenie">
        <ul class="example">
            <li>Wypożyczenie:
                <strong><xsl:value-of select="data-wypozyczenia"/></strong>
            </li>
            <li>Zwrot:
                <strong><xsl:value-of select="data-zwrotu"/></strong>
            </li>

            <xsl:for-each select="key('rel',idPoj)">
                <li>Model:

                    <xsl:value-of select="model"/></li>
                <li>Marka:

                    <xsl:value-of select="marka"/></li>
                <li>Nadwozie:

                    <xsl:value-of select="nadwozie"/></li>
                <li>Rocznik:

                    <xsl:value-of select="rocznik"/></li>
                <li>Kolor:

                    <xsl:value-of select="kolor"/></li>
                <li>Moc:

                    <xsl:value-of select="moc"/>KM</li>
            </xsl:for-each>
        </ul>
    </xsl:template>

    <xsl:template match="adres">
        <p><xsl:value-of select="miejscowosc"/>
            <xsl:text>, </xsl:text>

            <xsl:value-of select="ulica"/>
            <xsl:text> </xsl:text>

            <xsl:value-of select="nr-domu"/>
        </p>
    </xsl:template>

</xsl:stylesheet>
