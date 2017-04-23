package com.kaftanatiy.CourseWork2017Program1;

import com.kaftanatiy.CourseWork2017Program1.primitives.MyMatrix;
import com.kaftanatiy.CourseWork2017Program1.primitives.MyVector;
import com.kaftanatiy.CourseWork2017Program1.threads.TaskControl;
import com.kaftanatiy.CourseWork2017Program1.threads.TaskWorker;

public class Main {
    private static int N = 8;
    private static int P = 4;
    private static int H = N / P;

    public static final int maxValue = 5;

    public static long startTime = 0;
    public static long endTime = 0;


    private static MyMatrix MA = new MyMatrix(N);
    private static MyMatrix MC = new MyMatrix(N);
    private static MyMatrix MK = new MyMatrix(N);
    private static MyVector Z = new MyVector(N);

    public static void main(String[] args) {
        if(P > N) {
            P = N;
            H = 1;
        }
        Thread[] tasks = new Thread[P];
        TaskControl monitor = new TaskControl();

        for (int i = 0; i < P; i++) {
            tasks[i] = new Thread(new TaskWorker(i, monitor));
        }

        startTime = System.currentTimeMillis();
        for (int i = 0; i < P; i++) {
            tasks[i].start();
        }
    }



    public static int getN() {
        return N;
    }

    public static int getP() {
        return P;
    }

    public static int getH() {
        return H;
    }

    public static MyMatrix getMA() {
        return MA;
    }

    public static MyMatrix getMC() {
        return MC;
    }

    public static MyMatrix getMK() {
        return MK;
    }

    public static MyVector getZ() {
        return Z;
    }

    public static long getTime() {
        return endTime - startTime;
    }
}
