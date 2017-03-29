package com.kaftanatiy.CourseWork2017Program1.threads;

import com.kaftanatiy.CourseWork2017Program1.primitives.MyVector;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

/**
 * Recursive task for fork join
 * @author Bogdan Kaftanatiy
 */
public class MyRecursiveMaxTask extends RecursiveTask<Integer> {
    private MyVector vector;

    public MyRecursiveMaxTask(MyVector vector) {
        this.vector = vector;
    }

    @Override
    protected Integer compute() {
        if(vector.getDimension() > 10) {
            List<MyRecursiveMaxTask> subtasks = createSubtasks();

            for(MyRecursiveMaxTask subtask : subtasks) {
                subtask.fork();
            }

            int result = Integer.MIN_VALUE;
            for(MyRecursiveMaxTask subtask : subtasks) {
                int temp = subtask.join();
                if(temp > result)
                    result = temp;
            }
            return result;
        }

        else
            return vector.getMaxElement(0, vector.getDimension());
    }

    public List<MyRecursiveMaxTask> createSubtasks() {
        List<MyRecursiveMaxTask> subtasks = new ArrayList<>();

        MyRecursiveMaxTask subtask1 = new MyRecursiveMaxTask(this.vector.getPart(0, this.vector.getDimension()/2));
        MyRecursiveMaxTask subtask2 = new MyRecursiveMaxTask(this.vector.getPart(this.vector.getDimension()/2 + 1, this.vector.getDimension()));

        subtasks.add(subtask1);
        subtasks.add(subtask2);

        return subtasks;
    }
}
