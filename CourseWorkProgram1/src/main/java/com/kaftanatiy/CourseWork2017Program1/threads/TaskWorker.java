package com.kaftanatiy.CourseWork2017Program1.threads;

import com.kaftanatiy.CourseWork2017Program1.Main;
import com.kaftanatiy.CourseWork2017Program1.primitives.MyMatrix;
import com.kaftanatiy.CourseWork2017Program1.primitives.MyVector;

/**
 * Class to execute the task
 * @author Bogdan Kaftanatiy
 */
public class TaskWorker implements Runnable {
    private int tid;
    private TaskControl monitor;

    private MyMatrix MOcopy;
    private MyMatrix MBcopy;
    private int alpha_copy;

    public TaskWorker(int tid, TaskControl monitor) {
        this.monitor = monitor;
        this.tid = tid;
    }

    @Override
    public void run() {
        System.out.println("Thread " + tid + ": start execution");
        if (tid == 0) {
            monitor.inputMB();
            monitor.inputMO();

            monitor.signalInputDone();
        }

        if (tid == Main.getP() - 1) {
            Main.getMC().generate(Main.maxValue);
            Main.getMK().generate(Main.maxValue);
            Main.getZ().generate(Main.maxValue);

            monitor.signalInputDone();
        }

        monitor.waitInput();

        int startIndex = tid * Main.getH();
        int endIndex = (tid != Main.getP() - 1) ? (tid + 1) * Main.getH() : Main.getN();


        int alpha_i = Main.getZ().getMaxElement(startIndex, endIndex);
        monitor.computeMaxAlpha(alpha_i);

        monitor.signalMaxDone();
        monitor.waitMax();

        MOcopy = monitor.copyMO();
        MBcopy = monitor.copyMB();
        alpha_copy = monitor.copyAlpha();

        for (int i = 0; i < Main.getN(); i++){
            for (int j = startIndex; j < endIndex; j++){
                int M1 = 0;
                int M2 = 0;
                for (int k = 0; k < Main.getN(); k++){
                    M1 += MBcopy.get(i, k) * Main.getMC().get(k, j);
                    M2 += MOcopy.get(i, k) * Main.getMK().get(k, j);
                }
                int value = M1 + alpha_copy * M2;
                Main.getMA().set(i, j, value);
            }
        }

        if (tid == 0)
            monitor.waitCalc();
        else
            monitor.signalCalcDone();

        if (tid == 0) {
            if(Main.getMA().getDimension() < 10)
                System.out.println("Result MA:\n" + Main.getMA());
            else
                System.out.println("Result was calculated. Matrix is too large");
        }

        System.out.println("Thread " + tid + ": finish execution");
    }
}



















