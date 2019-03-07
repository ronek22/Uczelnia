package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        int CurrentDepth, MaxDepth;
        CurrentDepth = MaxDepth = 0;
        String Expression;

        System.out.println("Podaj wyrażenie:");
        Scanner scan = new Scanner(System.in);
        Expression = scan.next();

        // przejrzenie literka po literce
        for(int i = 0; i < Expression.length();i++){
            // Operowanie na kolejnych znakach, znak znajduje sie w zmiennej c
            char c = Expression.charAt(i);
            if(c=='('){
                CurrentDepth++;
                if(CurrentDepth > MaxDepth){
                    MaxDepth = CurrentDepth;
                }
            } else if(c==')'){
                CurrentDepth--;
            }
        }

        System.out.println("Poziom zaglebienie nawiasow wyrazenia: "+ Expression+" jest rowny "+MaxDepth);


	// write your code here
    }
}
