//#include <ArxTypeTraits.h>
#include <ClusterCollection.h>

/*
 * Example how to work with ClusterAlgorithm
 * Separete by first N differneces between neighboring elements
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

void setup() {
  Serial.begin(9600);
  const int array[]{1,1,1,  3,3,  7,7,7,  14,15,16};
  const size_t arrLength = sizeof(array)/sizeof(const int);

  Cluster<const int> cl(&array[0], &array[arrLength]);
  // DO NOT USE: ClusterAlgorithm<const int> clAlgo(new Cluster<const int>(&array[0], &array[arrLength]));
  // because you won't have an accession to the output cluster
  ClusterAlgorithm<const int> clAlgo(cl); 
  // From this statement ClusterAlgorithm have an accession to change cluster's borders
  // Some of the algorithms also can swap elements in the original array

  clAlgo.separateByDiff(4);  
  printCluster(cl);
}

void loop() {}
