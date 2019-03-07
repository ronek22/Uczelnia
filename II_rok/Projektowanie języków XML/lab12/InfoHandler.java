import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;
import org.xml.sax.helpers.DefaultHandler;

/**Przyklad ContentHandlera.
 * Informuje o niektorych zdarzeniach SAX wypisujac tekst na standardowe wyjscie.
 * @author Patryk Czarnik
 */
public class InfoHandler extends DefaultHandler {

  /**Domyslny konstruktor. */
  public InfoHandler() {
    super();
  }

  /* Metody interfejsu ContentHandler: */

  /**Informuje o zdarzeniu "wezel tekstowy".
   * @see org.xml.sax.helpers.DefaultHandler#characters(char[], int, int)
   */
  @Override
  public void characters(char[] aCh, int aStart, int aLength) throws SAXException {
    /* obcinamy napis jesli bylby za dlugi do wypisania */
    aLength = (aLength <= 512) ? aLength : 512;
    
    String napis = new String(aCh, aStart, aLength);
    System.out.print("CHARACTERS: ");
    System.out.println(napis);
  }

  /**Informuje o zdarzeniu "pocztaek elementu".
   * @see org.xml.sax.helpers.DefaultHandler#startElement(java.lang.String, java.lang.String, java.lang.String, org.xml.sax.Attributes)
   */
  @Override
  public void startElement(String aUri, String aLocalName, String aName, Attributes aAttributes) throws SAXException {
    System.out.println("START_ELEMENT qName="+aName+" URI="+aUri+" localName="+aLocalName
        +" attributes: "+aAttributes.getLength());
  }

  /**Informuje o zdarzeniu "koniec elementu".
   * @see org.xml.sax.helpers.DefaultHandler#endElement(java.lang.String, java.lang.String, java.lang.String)
   */
  @Override
  public void endElement(String aUri, String aLocalName, String aName) throws SAXException {
    System.out.println("END_ELEMENT qName="+aName+" URI="+aUri+" localName="+aLocalName);
  }

  /* Metody interfejsu ErrorHandler: */
  
  /**Informuje o zwyklym bledzie.
   * @see org.xml.sax.helpers.DefaultHandler#error(org.xml.sax.SAXParseException)
   */
  @Override
  public void error(SAXParseException e) throws SAXException {
    System.err.println("ERROR: "+e.getMessage());
  }

  /**Informuje o powaznym bledzie.
   * @see org.xml.sax.helpers.DefaultHandler#fatalError(org.xml.sax.SAXParseException)
   */
  @Override
  public void fatalError(SAXParseException e) throws SAXException {
    System.err.println("FATAL_ERROR: "+e.getMessage());
  }

  /**Informuje o ostrzezeniu.
   * @see org.xml.sax.helpers.DefaultHandler#warning(org.xml.sax.SAXParseException)
   */
  @Override
  public void warning(SAXParseException e) throws SAXException {
    System.err.println("WARNING: "+e.getMessage());
  }
}
