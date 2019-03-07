import java.io.IOException;
import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * Algorytmy Numeryczne - Zadanie 2
 * Macierze
 * Autor: Jakub Ronkiewicz, 238155
 * Informatyka: III rok sp. Tester programista gr. 1
 */
public class Matrix<T> {
    private int N; // wielkosc macierzy
    private T[][] data; // tu przechowuje macierz
    private T[] val; // wartosci z pliku

    // Kwadratowa macierz + wypelnienie
    public Matrix(int m, T[] values){
        this.N = m;
        data = (T[][]) new Object[N][N];
        val = values;
        fill(data, values);
    }

    // wypelnienie macierzy wartosciami
    public void fill(T[][] arr, T[] values){
        if( N * N != values.length)
            System.out.println("Nieodpowiednia ilosc wartości");
        else{
            int z = 0;
            for(int i = 0; i<N; i++){
                for(int j = 0; j<N; j++){
                    arr[i][j] = values[z++];
                }
            }
        }

    }

    // wypelnienie wektora wartosciami
    public void fill(T[] arr, T[] values){
        if( N != values.length)
            System.out.println("Nieodpowiednia ilosc wartości");
        else{
            for(int i = 0; i<N; i++){
                    arr[i] = values[i];
            }
        }
    }

    // dodawnie macierzy
    public Matrix addMatrix(T[][] matrix){
        // sprawdza czy dodawane macierze sa rowych wielkosci
        if ((matrix.length != data.length) ||
                (matrix[0].length != data[0].length)){
            throw new RuntimeException("Macierze nie sa tych samych wielkosci.");
        }

        // utworzenie tablicy tymczasowej wypelnionej zerami
        T[] temp = (T[])Array.newInstance(data[0][0].getClass(), N*N);
        for(int i = 0; i<N; i++){
            temp[i] = zero();
        }

        // wynik dodawnia dwoch macierzy w tymczasowej
        int z = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                temp[z++] = add(data[i][j], matrix[i][j]);
            }
        }

        // zwracam nowa macierz wypelniania wartosciami tymczasowej
        return new Matrix(N, temp);
    }

    // analogicznie do dodawnia tylko ze mnozy
    public Matrix mulMatrix(T[][] matrix){
        @SuppressWarnings("unchecked")
        T[] temp = (T[])Array.newInstance(data[0][0].getClass(), N*N);
        //Fill result array with zeros
        for(int i = 0; i<N*N; i++)
                temp[i] = zero();

        int z = 0;
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                for(int k = 0; k<N; k++){
                    temp[z] = add(temp[z], mul(data[i][k], matrix[k][j]));
                }
                z++;
            }
        }

        return new Matrix(N, temp);
    }

    // mnozenie macierzy przez wektor zwracamy wektor(tablica jednowymiarowa)
    public T[] mulMatrix(T[] vector){
        if(N != vector.length){
            throw new RuntimeException("Wektor musi miec tyle wartosci, co macierz kolumn");
        }

        @SuppressWarnings("unchecked")
        T[] result = (T[]) Array.newInstance(data[0][0].getClass(), N);
        //Fill result array with zeros
        for(int i = 0; i<N; i++){
                result[i] = zero();
        }

        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                    result[i] = add(result[i], mul(data[i][j], vector[j]));
                }
            }

        return result;
    }


    public T[] solve(T[] B){
        if(N != B.length)
            throw new RuntimeException("Wektor musi miec tyle wartosci, co macierz kolumn");

        // kopia tymczasowa wektora B
        T[] bTemp = (T[])Array.newInstance(data[0][0].getClass(), N);

        for(int i = 0; i < N; i++){
            bTemp[i] = B[i];
        }


        T pivot, factor;
        // kopia tymczasowa macierzy
        T[][] temp = (T[][])Array.newInstance(data[0][0].getClass(), N, N);
        fill(temp, val);


        for(int i = 0; i < N; i++){
            pivot = temp[i][i];

            for(int j = i; j < N; j++)
                temp[i][j] = div(temp[i][j], pivot);
            bTemp[i] = div(bTemp[i], pivot);

            for(int k = i+1; k<N; k++){
                factor = temp[k][i];
                for(int j = i; j < N; j++){
                    temp[k][j] = sub(temp[k][j], mul(temp[i][j], factor));
                }
                bTemp[k] = sub(bTemp[k], mul(bTemp[i], factor));
            }
        }

        // po tej petli mamy 1 na przekatnej i zera pod nimi, ale nie ma zer nad przekatna
        // backSubstitution rozwiazuje macierz od dolu
        T[] x = backSubstitution(temp, bTemp);

        return x;

    }

    public T[] solvePartial(T[] B){
        if(N != B.length)
            throw new RuntimeException("Wektor musi miec tyle wartosci, co macierz kolumn");

        T[] bTemp = (T[])Array.newInstance(data[0][0].getClass(), N);

        for(int i = 0; i < N; i++){
            bTemp[i] = B[i];
        }

        T[][] temp = (T[][])Array.newInstance(data[0][0].getClass(), N, N);
        fill(temp, val);

        // TYMCZASOWE UTWORZONE

        for(int p = 0; p < N; p++){
            // find pivot row and swap
            int max = p; // indeks najwiekszego
            for(int i = p+1; i < N; i++){
                if(greater((abs(temp[i][p])), (abs(temp[max][p]))))
                    max = i;
            }

            swapRows(temp, p, max);
            swap(bTemp, p, max);


            // jesli 0 to w calej kolumnie sa tylko 0, uklad nierozwiazywalny
            if(((temp[p][p]) == zero())){
                throw new ArithmeticException("Matrix is singular or nearly singular");
            }

            // pivot within A and B
            for(int i = p+1; i < N; i++){
                T alpha = div(temp[i][p], temp[p][p]);
                bTemp[i] = sub(bTemp[i], mul(alpha, bTemp[p]));

                for(int j = p; j < N; j++){
                    temp[i][j] = sub(temp[i][j], mul(alpha, temp[p][j]));
                }
            }
        }

        T[] x = backSubstitution(temp, bTemp);
        return x;
    }

    public T[] solveFull(T[] B){
        if(N != B.length)
            throw new RuntimeException("Wektor musi miec tyle wartosci, co macierz kolumn");

        T[] bTemp = (T[])Array.newInstance(data[0][0].getClass(), N);

        for(int i = 0; i < N; i++){
            bTemp[i] = B[i];
        }

        T[][] temp = (T[][])Array.newInstance(data[0][0].getClass(), N, N);
        fill(temp, val);
        // TYMCZASOWE UTWORZONE

        // TABLICA DO ZAPAMIETENIA KOLEJNOSCI ZMIENNYCH
        int[] order = new int[N];
        Arrays.setAll(order, (index) -> index); // ponumerowanie tablicy od 0 do N-1

        for(int p = 0; p < N; p++){
            int max_col = p, max_row = p; // indeks najwiekszego
            for(int i = p; i < N; i++){
                for(int j = p; j < N; j++){
                    if(greater((abs(temp[i][j])), (abs(temp[max_row][max_col])))) {
                        max_row = i;
                        max_col = j;
                    }
                }
            }

            if(p != max_row)
                swapRows(temp, p, max_row);
                swap(bTemp, p, max_row);
            if(p != max_col)
                swapCols(temp, p, max_col, order);

            // jesli 0 to w calej kolumnie sa tylko 0, uklad nierozwiazywalny
            if(((temp[p][p]) == zero())){
                throw new ArithmeticException("Matrix is singular or nearly singular");
            }

            // pivot within A and B
            for(int i = p+1; i < N; i++){
                T alpha = div(temp[i][p], temp[p][p]);
                bTemp[i] = sub(bTemp[i], mul(alpha, bTemp[p]));

                for(int j = p; j < N; j++)
                    temp[i][j] = sub(temp[i][j], mul(alpha, temp[p][j]));
            }
        }


        T[] x = backSubstitution(temp ,bTemp);
        T[] result = (T[])Array.newInstance(data[0][0].getClass(), N);

        // uklad rozwiazany, ale trzeba posegregowac wyniki, po wielkorotnych zamianach kolumn
        int i = 0;
        for (int ind: order){
            result[ind] = x[i];
            i++;
        }

        return result;
    }

    private T[] backSubstitution(T[][] arr, T[] B){
        // solve equation with upper triangle
        @SuppressWarnings("unchecked")
        T[] x = (T[]) Array.newInstance(data[0][0].getClass(), N);
        for(int i = N - 1; i >= 0; i--){
            T sum = zero();
            for(int j = i+1; j < N; j++){
                sum = add(sum, mul(arr[i][j], x[j]));
            }
            x[i] = div(sub(B[i],sum), arr[i][i]);

        }
        return x;
    }

    public Float[] val2Float(Fraction[] values){
        Float[] converted = new Float[N*N];
        for(int i = 0; i < N*N; i++){
            converted[i] = values[i].getNumerator().floatValue() / values[i].getDenominator().floatValue();
        }
        return converted;
    }

    public Double[] val2Double(Fraction[] values){
        Double[] converted = new Double[N*N];
        for(int i = 0; i < N*N; i++){
            converted[i] = values[i].getNumerator().doubleValue() / values[i].getDenominator().doubleValue();
        }
        return converted;
    }

    public T[] get1D(){
        @SuppressWarnings("unchecked")
        T[] temp = (T[])Array.newInstance(data[0][0].getClass(), N*N);


        int z = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                temp[z++] = data[i][j];
            }
        }

        return temp;
    }

    public void printMat(){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                System.out.print(String.format("%-10s ", data[i][j]));
            }
            System.out.println();
        }
        System.out.println();
    }

    public void printMat(T[] ext){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                System.out.print(String.format("%-10s ", data[i][j]));
            }
            System.out.print(ext[i]);
            System.out.println();
        }
        System.out.println();
    }

    public void printMat(T[][] array, T[] ext){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                System.out.print(String.format("%-10s ", array[i][j]));
            }
            System.out.print(ext[i]);
            System.out.println();
        }
        System.out.println();
    }


    public T[][] getMatrix(){
        return data;
    }

    private void swapRows(T[][] arr,int rowA, int rowB){
        T tmpRow[] = arr[rowA];
        arr[rowA] = arr[rowB];
        arr[rowB] = tmpRow;
    }

    private void swapCols(T[][] arr,int colA, int colB, int[] ord){
        // swap columns and int array of order variable
        for(int i = 0; i<N; i++){
            T tmp = arr[i][colA];
            arr[i][colA] = arr[i][colB];
            arr[i][colB] = tmp;
        }
        swap(ord, colA, colB);
    }

    private void swap(T[] arr, int a, int b){
        T temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    private void swap(int[] arr, int a, int b){
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    public int getN(){
        return N;
    }

    @SuppressWarnings("unchecked")
    private <T> T add(T one, T two){
        if(one.getClass() == Float.class){
            return (T) Float.valueOf(((Float) one).floatValue() + ((Float) two).floatValue());
        }
        if(one.getClass() == Double.class){
            return (T) Double.valueOf(((Double) one).doubleValue() + ((Double) two).doubleValue());
        }
        if(one.getClass() == Fraction.class){
            return (T) ((Fraction) one).add(((Fraction) two));
        }
        throw new RuntimeException("NIEOBSLUGIWANY TYP");
    }

    @SuppressWarnings("unchecked")
    private <T> T mul(T one, T two){
        if(one.getClass() == Float.class){
            return (T) Float.valueOf(((Float) one).floatValue() * ((Float) two).floatValue());
        }
        if(one.getClass() == Double.class){
            return (T) Double.valueOf(((Double) one).doubleValue() * ((Double) two).doubleValue());
        }
        if(one.getClass() == Fraction.class){
            return (T) ((Fraction) one).multiply(((Fraction) two));
        }
        throw new RuntimeException("NIEOBSLUGIWANY TYP");
    }

    @SuppressWarnings("unchecked")
    private <T> T div(T one, T two){
        if(one.getClass() == Float.class){
            return (T) Float.valueOf(((Float) one).floatValue() / ((Float) two).floatValue());
        }
        if(one.getClass() == Double.class){
            return (T) Double.valueOf(((Double) one).doubleValue() / ((Double) two).doubleValue());
        }
        if(one.getClass() == Fraction.class){
            return (T) ((Fraction) one).divide(((Fraction) two));
        }
        throw new RuntimeException("NIEOBSLUGIWANY TYP");
    }

    @SuppressWarnings("unchecked")
    private <T> T sub(T one, T two){
        if(one.getClass() == Float.class){
            return (T) Float.valueOf(((Float) one).floatValue() - ((Float) two).floatValue());
        }
        if(one.getClass() == Double.class){
            return (T) Double.valueOf(((Double) one).doubleValue() - ((Double) two).doubleValue());
        }
        if(one.getClass() == Fraction.class){
            return (T) ((Fraction) one).subtract(((Fraction) two));
        }
        throw new RuntimeException("NIEOBSLUGIWANY TYP");
    }

    @SuppressWarnings("unchecked")
    private <T> boolean greater(T one, T two){
        if(one.getClass() == Float.class){
            return  (boolean) ((((Float) one).floatValue()) > ((Float) two).floatValue());
        }
        if(one.getClass() == Double.class){
            return (boolean) (((Double) one).doubleValue() > ((Double) two).doubleValue());
        }
        if(one.getClass() == Fraction.class){
            return ((Fraction) one).greater(((Fraction) two));
        }
        throw new RuntimeException("NIEOBSLUGIWANY TYP");
    }

    @SuppressWarnings("unchecked")
    private <T> T abs(T one){
        if(one.getClass() == Float.class){
            return (T) Float.valueOf(Math.abs((Float)one));
        }
        if(one.getClass() == Double.class){
            return (T) Double.valueOf(Math.abs((Double)one));
        }
        if(one.getClass() == Fraction.class){
            return (T) (((Fraction) one).abs());
        }
        throw new RuntimeException("NIEOBSLUGIWANY TYP");
    }

    @SuppressWarnings("unchecked")
    private <T> T zero(){
        if(data[0][0].getClass() == Float.class){
            return (T) Float.valueOf(0);
        }
        if(data[0][0].getClass() == Double.class){
            return (T) Double.valueOf(0);
        }
        if(data[0][0].getClass() == Fraction.class){
            return (T) Fraction.zero();
        }
        throw new RuntimeException("NIEOBSLUGIWANY TYP");
    }

}
