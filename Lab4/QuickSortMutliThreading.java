import java.io.*;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.*; 

public class QuickSortMutliThreading
	extends RecursiveTask<Integer> {

	int start, end;
	int[] arr;

	
	private int partition(int start, int end,
						int[] arr)
	{

		int i = start, j = end;

		// Decide random pivot
		int pivote = new Random()
						.nextInt(j - i)
					+ i;

		// Swap the pivoted with end
		// element of array;
		int t = arr[j];
		arr[j] = arr[pivote];
		arr[pivote] = t;
		j--;

		// Start partitioning
		while (i <= j) {

			if (arr[i] <= arr[end]) {
				i++;
				continue;
			}

			if (arr[j] >= arr[end]) {
				j--;
				continue;
			}

			t = arr[j];
			arr[j] = arr[i];
			arr[i] = t;
			j--;
			i++;
		}

		// Swap pivoted to its
		// correct position
		t = arr[j + 1];
		arr[j + 1] = arr[end];
		arr[end] = t;
		return j + 1;
	}

	// Function to implement
	// QuickSort method
	public QuickSortMutliThreading(int start,
								int end,
								int[] arr)
	{
		this.arr = arr;
		this.start = start;
		this.end = end;
	}

	@Override
	protected Integer compute()
	{
		// Base case
		if (start >= end)
			return null;

		// Find partition
		int p = partition(start, end, arr);

		// Divide array
		QuickSortMutliThreading left
			= new QuickSortMutliThreading(start,
										p - 1,
										arr);

		QuickSortMutliThreading right
			= new QuickSortMutliThreading(p + 1,
										end,
										arr);

		// Left subproblem as separate thread
		left.fork();
		right.compute();

		// Wait untill left thread complete
		left.join();

		// We don't want anything as return
		return null;
	}

	// Driver Code
	public static void main(String args[])
	{
		Scanner sc= new Scanner(System.in); 
		System.out.print("Enter the number of elements:");
		int n=sc.nextInt(); 
		int arr[] = new int[n];
		Random random = new Random();
		System.out.println("Randomly Generated array:");
		for(int i=0; i<n; i++){

			arr[i] = random.nextInt(n+(n-1))-(n-1);
			System.out.print(arr[i] + " ");
		}

		// Forkjoin ThreadPool to keep
		// thread creation as per resources
		ForkJoinPool pool
			= ForkJoinPool.commonPool();

		// Start the first thread in fork
		// join pool for range 0, n-1
		pool.invoke(
			new QuickSortMutliThreading(
				0, n - 1, arr));

		// Print shorted elements
		System.out.println("\nSortedd Array:");
		for (int i = 0; i < n-1; i++)
			System.out.print(arr[i] + " ");

			System.out.println("\n");
	}
	
}
