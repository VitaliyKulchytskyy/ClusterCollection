#include <ClusterCollection.h>

/*
 * Example how to work with array (non-class types) in ClusterCollection library
 * 
 * 
 * In this example were considered next functions:
 * .insert(indexOfElement) - to insert new border in the "indexOfElement" position (same function like .insert() in the stl::set)
 * [cluster_index].remove() - to remove "cluster_index" cluster
 * .clear() - to delete all insereted borders
 * [cluster_index].rshift(shiftSteps=1) - to shift "cluster_index" border to right side "shiftSteps" times, or 1 time as default
 * [cluster_index].lshift(shiftSteps=1) - to shift "cluster_index" border to left side "shiftSteps" times, or 1 time as default
 */

// This function to print information about each cluster
/*
 * .getClusterAmount() - to get amount of clusters (as a default cluster amount = 1) (return clt::type_clAmount, which alias from uint8_t)
 * [cluster_index].length() - to get length of "cluster_index" cluster               (return clt::type_elemAmount, which alias from uint16_t)
 * [cluster_index].getValue(indexOfElement) - to get "indexOfElement" element from "cluster_index" cluster   (return T)
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
    const int array[]{1, 1, 1, 1, 1, 5, 5, 5};
    const size_t arrLength = sizeof(array)/sizeof(const int);

    // [Initialization of Cluster]
    Cluster<const int> cl(&array[0], &array[arrLength]);
    /*
     * {0}: |1| |1| |1| |1| |1| |5| |5| |5| |-|
     *       0   1   2   3   4   5   6   7
     *      (0) (1) (2) (3) (4) (5) (6) (7) (8)
     *       H                               T
     *  ---------------------------------------
     *  Legend:
     *  H - head (pointer on the 0 element of your array)
     *  T - tail (pointer on the (last element index) + (1) of your array)
     *  {x} - index of cluster
     *  |y| - element which contains in the {x} cluster
     *  |-| - element which doesn't contain in the original array
     *   z  - index of |y| element, which contains in {x} cluster
     *  (i) - index of the orignal array
     */

    // [Method: INSERT]
    // cl.insert(indexOfElement) - to insert new border in the "indexOfElement" position (same function like .insert() in the stl::set)
    Serial.println("[INSERT]");
    cl.insert(5); // on the left-hand side will be 0 cluster, on the right-hand side will be 1 cluster
    /*
     * {0}: |1| |1| |1| |1| |1| |5| |5| |5|
     *       0   1   2   3   4   5   6   7
     *          (left-hand side) ^ (right-hand side)
     *      (0) (1) (2) (3) (4) (5) (6) (7)            
     * this operation also will create new
     * cluster. So, we have 2 clusters:
     * 
     * {0}: |1| |1| |1| |1| |1|
     *       0   1   2   3   4
     *      (0) (1) (2) (3) (4)
     *      
     * {1}: |5| |5| |5| 
     *       0   1   2  
     *      (5) (6) (7)
     */
    // print all clusters
    printCluster(cl);

    // [Method: REMOVE]
    // cl[cluster_index].remove() - to remove "cluster_index" cluster
    // ! You can't remove 0 cluster !
    // ! You can't call this function without [] operator !
    Serial.println("\n[REMOVE]");
    cl[1].remove();
    /*
     *           {0}: |1| |1| |1| |1| |1|
     *                 0   1   2   3   4
     * Remove -> {1}: |5| |5| |5| 
     *                 0   1   2  
     */
    // print all clusters
    printCluster(cl);

    // [Method: INSERT_FULL]
    Serial.println("\n[INSERT_FULL]");
    cl.insert(5); // 3 cluster
    cl.insert(2); // 1 cluster
    cl.insert(2); // won't added
    cl.insert(3); // 2 cluster
    /*
     * {0}: |1| |1|
     *       0   1
     *      (0) (1)
     *       
     * {1}: |1|
     *       0   
     *      (2)
     *       
     * {2}: |1| |1|      
     *       0   1
     *      (3) (4)
     *       
     * {3}: |5| |5| |5|
     *       0   1   2
     *      (5) (6) (7)
     */
    // print all clusters
    printCluster(cl);
    
    // [Method: CLEAR]
    // cl.clear() - to delete all insereted borders
    Serial.println("\n[CLEAR]");
    cl.clear();
    // print all clusters
    printCluster(cl);
    
    // [Method: RSHIFT]
    // cl[cluster_index].rshift(shiftSteps=1) - to shift "cluster_index" border to right side "shiftSteps" times, or 1 time as default
    // ! You can't shift 0 cluster border !
    Serial.println("\n[RSHIFT]");
    // arrange
    cl.insert(5);
    // act
    /* Before rshift
     * {0}: |1| |1| |1| |1| |1|
     *       0   1   2   3   4
     *      (0) (1) (2) (3) (4)
     *       
     * {1}: |5| |5| |5| 
     *       0   1   2  
     *      (5) (6) (7)
     */
    cl[1].rshift(2);
    /* After rshift:
     * {0}: |1| |1| |1| |1| |1| |5| |5|
     *       0   1   2   3   4   5   6
     *      (0) (1) (2) (3) (4) (5) (6) 
     *       
     * {1}: |5| 
     *       0         
     *      (7)
     */
    // print all clusters
    printCluster(cl);
        
    // [Method: LSHIFT]
    // cl[cluster_index].lshift(shiftSteps=1) - to shift "cluster_index" border to left side "shiftSteps" times, or 1 time as default
    // ! You can't shift 0 cluster border !
    Serial.println("\n[RSHIFT]");
    // arrange
    cl[1].remove();
    cl.insert(5);
    // act
    /* Before lshift
     * {0}: |1| |1| |1| |1| |1|
     *       0   1   2   3   4
     *      (0) (1) (2) (3) (4)
     *       
     * {1}: |5| |5| |5| 
     *       0   1   2  
     *      (5) (6) (7) 
     */
    cl[1].lshift(2);
    /* After lshift:
     * {0}: |1| |1| |1|
     *       0   1   2 
     *      (0) (1) (2)
     *       
     * {1}: |1| |1| |5| |5| |5| 
     *       0   1   2   3   4   
     *      (3) (4) (5) (6) (7)
     */
    // print all clusters
    printCluster(cl);
}

void loop() {}
