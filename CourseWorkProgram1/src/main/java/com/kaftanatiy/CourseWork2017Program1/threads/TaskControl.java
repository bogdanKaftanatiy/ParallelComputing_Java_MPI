package com.kaftanatiy.CourseWork2017Program1.threads;

import com.kaftanatiy.CourseWork2017Program1.Main;
import com.kaftanatiy.CourseWork2017Program1.primitives.MyMatrix;

/**
 * Monitor class to synchronize threads
 * @author Bogdan Kaftanatiy
 */
public class TaskControl {
    private int inputCount = 0;
    private int maxCount = 0;
    private int calcCount = 0;

    private int alpha = Integer.MIN_VALUE;
    private MyMatrix MO = new MyMatrix(Main.getN());
    private MyMatrix MB = new MyMatrix(Main.getN());

    public synchronized void waitInput() {
        while (inputCount < 2) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public synchronized void waitCalc() {
        while (calcCount < Main.getP() - 1) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public synchronized void waitMax() {
        while (maxCount < Main.getP()) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    public synchronized void inputMO() {
        MO.generate(Main.maxValue);
    }

    public synchronized void inputMB() {
        MB.generate(Main.maxValue);
    }

    public synchronized void computeMaxAlpha(int alpha_i) {
        if(alpha_i > alpha)
            alpha = alpha_i;
    }


    public synchronized MyMatrix copyMO() {
        return new MyMatrix(MO);
    }

    public synchronized MyMatrix copyMB() {
        return new MyMatrix(MB);
    }

    public synchronized int copyAlpha() {
        return alpha;
    }


    public synchronized void signalInputDone() {
        inputCount++;
        if(inputCount == 2)
            notifyAll();
    }

    public synchronized void signalCalcDone() {
        calcCount++;
        if (calcCount == Main.getP() - 1)
            notifyAll();
    }

    public synchronized void signalMaxDone() {
        maxCount++;
        if (maxCount == Main.getP())
            notifyAll();
    }
}
