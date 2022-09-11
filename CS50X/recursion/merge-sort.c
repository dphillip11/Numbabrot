#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <math.h>

void sort(int[], int);
void merge(int[], int, int[], int);

int main(void)
{
    int count = get_int("how many numbers?");
    int list[count];

    for (int i = 0; i < count; i++)
    {
        list[i] = get_int("%i:", i);
    }

    sort(list, count);

    for(int j = 0; j < count; j++)
    {
        printf("%i ", list[j]);
    }

    printf("\n");

}

void sort(int arr[], int length)
{
    if (length == 1)
    {
        return;
    }

    int midpoint = floor(length /2);

    int left_array[midpoint];
    int right_array[length - midpoint];

    for (int i = 0; i < midpoint; i ++)
    {
        left_array[i] = arr[i];
    }
    for (int j = midpoint; j < length; j ++)
    {
        right_array[j - midpoint] = arr[j];
    }

    sort(left_array, midpoint);
    sort(right_array, length - midpoint);
    merge(left_array, midpoint, right_array, length - midpoint);
    for (int k = 0; k < length; k++)
    {
        if (k < midpoint)
        {
            arr[k] = left_array[k];
        }
        else
        {
            arr[k] = right_array[k - midpoint];
        }
    }


}

void merge(int left[], int length_l, int right[], int length_r)
{
    int left_index = 0;
    int right_index = 0;
    int temp_arr[length_l + length_r];

    for (int i = 0; i < length_l + length_r; i++)
    {
        if (left[left_index] > right[right_index] && left_index < length_l)
        {
            temp_arr[i] = left[left_index];
            left_index ++;
        }
        else
        {
            if (right_index < length_r)
            {
                temp_arr[i] = right[right_index];
                right_index ++;
            }
            else
            {
                temp_arr[i] = left[left_index];
                left_index ++;
            }
        }
    }

    for (int j = 0; j < length_l + length_r; j++)
    {
        if (j < length_l)
        {
            left[j] = temp_arr[j];
        }
        else
        {
            right[j - length_l] = temp_arr[j];
        }
    }
}