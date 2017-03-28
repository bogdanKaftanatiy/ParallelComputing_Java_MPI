package com.kaftanatiy.CourseWork2017Program1.primitives;

import java.util.Random;

/**
 * Model of Vector with size N
 * @author Bogdan Kaftanatiy
 */
public class MyVector {
    private int dimension;
    private int[] array;

    public MyVector(int dimension) {
        this.dimension = dimension;
        array = new int[dimension];
    }

    public void generate(int maxValue) {
        Random generator = new Random();

        for (int i = 0; i < dimension; i++) {
            array[i] = generator.nextInt(maxValue);
        }
    }

    public int getMaxElement() {
        int result = Integer.MIN_VALUE;
        for (int i = 0 ; i < dimension; i++) {
            if(array[i] > result)
                result = array[i];
        }
        return result;
    }

    @Override
    public String toString() {
        String result = "";

        for (int i = 0; i < dimension; i++) {
            result += array[i] + "\t";
        }

        return result;
    }
}
