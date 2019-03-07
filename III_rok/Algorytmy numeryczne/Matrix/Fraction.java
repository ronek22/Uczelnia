import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.RoundingMode;


public final class Fraction implements Comparable<Fraction> {

    private static final BigInteger bigZero = BigInteger.valueOf( 0 );
    private static final BigInteger bigOne = BigInteger.valueOf( 1 );

    private BigInteger numerator;
    private BigInteger denominator;

    public Fraction(int num){
        init(BigInteger.valueOf(num),BigInteger.ONE);
    }
    public Fraction(int num, int den) {
        init(BigInteger.valueOf(num), BigInteger.valueOf(den));
    }
    public Fraction(BigInteger num, BigInteger den){
        init(num, den);
    }

    public Fraction(String fraction){
        String[] tokens = fraction.split("/");
        init(new BigInteger(tokens[0]), new BigInteger(tokens[1]));
    }

    private void init(BigInteger num, BigInteger den) {
        if (den.signum() == 0)
            throw new IllegalArgumentException("Zero denominator");

        // Simplify the fraction to the canonical form
        if (den.signum() == -1) {
            num = num.negate();
            den = den.negate();
        }
        BigInteger gcd = num.gcd(den);
        if (!gcd.equals(BigInteger.ONE)) {
            num = num.divide(gcd);
            den = den.divide(gcd);
        }
        numerator = num;
        denominator = den;
    }



    public Fraction multiply(Fraction frac){
        BigInteger num = numerator.multiply(frac.numerator);
        BigInteger den = denominator.multiply(frac.denominator);

        BigInteger gcd = num.gcd(den);
        if (!gcd.equals(BigInteger.ONE)) {
            num = num.divide(gcd);
            den = den.divide(gcd);
        }
        return new Fraction(num,den);
    }

    public Fraction divide(Fraction frac){
        BigInteger num = numerator.multiply(frac.denominator);
        BigInteger den = denominator.multiply(frac.numerator);

        BigInteger gcd = num.gcd(den);
        if (!gcd.equals(BigInteger.ONE)) {
            num = num.divide(gcd);
            den = den.divide(gcd);
        }
        return new Fraction(num,den);
    }

    public Fraction add(Fraction frac){
        BigInteger num = numerator.multiply(frac.denominator).add(frac.numerator.multiply(denominator));
        BigInteger den = denominator.multiply(frac.denominator);

        BigInteger gcd = num.gcd(den);
        if (!gcd.equals(BigInteger.ONE)) {
            num = num.divide(gcd);
            den = den.divide(gcd);
        }
        return new Fraction(num,den);
    }

    public Fraction subtract(Fraction frac){
        BigInteger num = numerator.multiply(frac.denominator).subtract(frac.numerator.multiply(denominator));
        BigInteger den = denominator.multiply(frac.denominator);

        BigInteger gcd = num.gcd(den);
        if (!gcd.equals(BigInteger.ONE)) {
            num = num.divide(gcd);
            den = den.divide(gcd);
        }
        return new Fraction(num,den);
    }

    public static Fraction zero(){
        BigInteger num = BigInteger.ZERO;
        BigInteger den = BigInteger.ONE;
        return new Fraction(num,den);
    }

    public boolean greater(Fraction frac){
        if(this.compareTo(frac) == 1)
            return true;
        return false;
    }

    public Fraction abs() {
        BigInteger num = numerator;
        if(num.signum() == -1)
            num = num.negate();
        return new Fraction(num, denominator);
    }


    public boolean equals(Object obj) {
        if (!(obj instanceof Fraction))
            return false;
        Fraction other = (Fraction)obj;
        return numerator.equals(other.numerator) && denominator.equals(other.denominator);
    }


    public int hashCode() {
        return numerator.hashCode() + denominator.hashCode();
    }


    public int compareTo(Fraction other) {
        return numerator.multiply(other.denominator).compareTo(other.numerator.multiply(denominator));
    }


    public String toString() {
        if(denominator.equals(BigInteger.ONE))
            return String.format("%d", numerator);
        else
            return String.format("%d/%d", numerator, denominator);
    }

    public Float toFloat(){
        return numerator.floatValue() / denominator.floatValue();
    }

    public Double toDouble(){
        int SCALE = 16;        // number of digits after the decimal place
        BigDecimal num   = new BigDecimal(numerator);
        BigDecimal den = new BigDecimal(denominator);
        BigDecimal quotient    = num.divide(den, SCALE, RoundingMode.HALF_EVEN);
        return quotient.doubleValue();
    }

    public BigInteger getNumerator(){
        return numerator;
    }

    public BigInteger getDenominator(){
        return denominator;
    }


}
