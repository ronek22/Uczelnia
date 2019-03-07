/*
 * Created on 2004-11-29
 */
import java.io.IOException;

import javax.xml.parsers.FactoryConfigurationError;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * @author Patryk Czarnik
 */
public class LiczbySAX {
  public static void main(String[] args) {
    if(args.length < 1) {
      System.out.println("Za malo parametrow");
      return;
    }

    try {
      SAXParserFactory factory = SAXParserFactory.newInstance();
      factory.setValidating(true);
      SAXParser parser = factory.newSAXParser();

      LiczbyHandler maxHandler = new LiczbyHandler();
      LiczbyHandler2 minHandler = new LiczbyHandler2();
      parser.parse(args[0], maxHandler);
      parser.parse(args[0], minHandler);

      System.out.println("Max(grupa==\"tak\"): "+maxHandler.getResult());
      System.out.println("Min(grupa==\"nie\"): "+minHandler.getResult());
      // System.out.println("")
    } catch (FactoryConfigurationError e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (SAXException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (ParserConfigurationException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (IOException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
  }

  private static class LiczbyHandler extends DefaultHandler
  {
	enum Stan {ZEWN, GRUPA, LICZBA};

    private int fMax = 0; // minimum
    private int fMin = 0; // maksimum
    private Stan fStan = Stan.ZEWN;
    private StringBuffer fBuf;

    public int getResult() {
      return fMax;
    }

    public void startElement(String uri, String localName, String qName,
        Attributes attributes) throws SAXException {
      if("grupa".equals(qName)) {
        String attrVal = attributes.getValue("wazne");
        if("tak".equals(attrVal))
          fStan = Stan.GRUPA;
      } else if("l".equals(qName)) {
        if(fStan == Stan.GRUPA) {
          fStan = Stan.LICZBA;
          fBuf = new StringBuffer();
        }
      }
    }

    public void endElement(String uri, String localName, String qName)
    throws SAXException {
      if("grupa".equals(qName)) {
        if(fStan == Stan.GRUPA) {
          fStan = Stan.ZEWN;
        }
      } else if("l".equals(qName)) {
        if(fStan == Stan.LICZBA) {
          fStan = Stan.GRUPA;
          try {
            // jesli obecna wartosc jest wieksza od dotychczasowej najwiekszej
            if(fMax<Integer.parseInt(fBuf.toString())) fMax = Integer.parseInt(fBuf.toString());
          } catch (NumberFormatException e) {
          }
        }
      }
    }
    public void characters(char[] ch, int start, int length)
        throws SAXException {
      if(fStan == Stan.LICZBA)
        fBuf.append(ch, start, length);
    }
  }

  private static class LiczbyHandler2 extends DefaultHandler {
  enum Stan {ZEWN, GRUPA, LICZBA};

    private boolean firstValue=false;
    private int fMin; // maksimum
    private Stan fStan = Stan.ZEWN;
    private StringBuffer fBuf;

    public int getResult() {
      return fMin;
    }

    public void startElement(String uri, String localName, String qName,
        Attributes attributes) throws SAXException {
      if("grupa".equals(qName)) {
        String attrVal = attributes.getValue("wazne");
        if("nie".equals(attrVal))
          fStan = Stan.GRUPA;
      } else if("l".equals(qName)) {
        if(fStan == Stan.GRUPA) {
          fStan = Stan.LICZBA;
          fBuf = new StringBuffer();
        }
      }
    }

    public void endElement(String uri, String localName, String qName)
    throws SAXException {
      if("grupa".equals(qName)) {
        if(fStan == Stan.GRUPA) {
          fStan = Stan.ZEWN;
        }
      } else if("l".equals(qName)) {
        if(fStan == Stan.LICZBA) {
          fStan = Stan.GRUPA;
          try {
            // jesli obecna wartosc jest wieksza od dotychczasowej najwiekszej
            if(firstValue==false || fMin>=Integer.parseInt(fBuf.toString())){
              fMin = Integer.parseInt(fBuf.toString());
              firstValue = true;
            }
          } catch (NumberFormatException e) {
          }
        }
      }
    }
    public void characters(char[] ch, int start, int length)
        throws SAXException {
      if(fStan == Stan.LICZBA)
        fBuf.append(ch, start, length);
    }
  }
}
