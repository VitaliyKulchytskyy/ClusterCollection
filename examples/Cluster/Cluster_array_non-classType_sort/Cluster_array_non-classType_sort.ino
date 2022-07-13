#include <ClusterCollection.h>

/*
 * Example how to sort certian cluster
 * This sort function won't be work for the array of struct or classes (check ClusterAlgorithm)
 */

template<typename T>
void printCluster(const Cluster<T> &clPrint) {
    if(!clPrint.isEmpty()) {
        Serial.print("- Clusters amount: ");
        Serial.println(clPrint.getClusterAmount());
        for (clt::type_clAmount i = 0; i < clPrint.getClusterAmount(); i++) {
            Serial.print("["); Serial.print(i); Serial.print("]"); Serial.print(" Length: "); Serial.println(clPrint[i].length());
            for (clt::type_elemAmount j = 0; j < clPrint[i].length(); j++) {
                Serial.println(clPrint[i].getValue(j));
            }
        }
    } else {
        Serial.println("[!] Empty cluster.");
    }
}

template<typename T>
void insertionSort(T arr[], clt::type_elemAmount n) 
{ 
    clt::type_elemAmount i, key, j; 
    for (i = 1; i < n; i++)
    { 
        key = arr[i]; 
        j = i - 1; 
  
        // Move elements of arr[0..i-1],  
        // that are greater than key, to one 
        // position ahead of their 
        // current position
        while (j >= 0 && arr[j] > key)
        { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
}

void setup() { 
  Serial.begin(9600);
  
  int array[]{1, 298, 43, 13, 51, 163, 97, 28, 192, 10};
  const size_t arrayLength = sizeof(array) / sizeof(int);

  Cluster<int> cl(&array[0], &array[arrayLength]);
  cl.insert(2);
  cl.insert(8);

  const clt::type_clAmount clIndex = 1;
  // In this case operator& will return pointer to the array element, which separate two cluster
  insertionSort(&cl[clIndex], cl[clIndex].length());
  Serial.println("[SORT_CLUSTER]");
  printCluster(cl);
}

void loop() {}
