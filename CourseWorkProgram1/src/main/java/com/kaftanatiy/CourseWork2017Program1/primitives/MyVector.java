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

    public MyVector(int[] array) {
        this.array = array;
        this.dimension = array.length;
    }

    public void generate(int maxValue) {
        Random generator = new Random();

        for (int i = 0; i < dimension; i++) {
            array[i] = generator.nextInt(maxValue);
        }
    }

    public int getMaxElement(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex > dimension || startIndex >= endIndex)
            throw new IllegalStateException();

        int result = Integer.MIN_VALUE;
        for (int i = startIndex ; i < endIndex; i++) {
            if(array[i] > result)
                result = array[i];
        }
        return result;
    }

    public MyVector getPart(int startIndex, int endIndex) {
        if(endIndex <= startIndex || endIndex > dimension || startIndex < 0)
            throw new IllegalStateException();

        int length = endIndex - startIndex;
        int[] resultArray = new int[length];
        System.arraycopy(this.array, startIndex, resultArray, 0, length);

        return new MyVector(resultArray);
    }

    public int getDimension() {
        return dimension;
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
