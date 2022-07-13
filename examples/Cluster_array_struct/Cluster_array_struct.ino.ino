#include <ClusterCollection.h>

/*
 * Example how to work with array of struct in ClusterCollection library 
 * 
 * For this case all cluster's methods will act in the same way as with non-class type arrays (check Cluster_array_non-classType)
 */

template<typename T>
void printCluster(const Cluster<T> &clPrint) {
    if(!clPrint.isEmpty()) {
        Serial.print("- Clusters amount: ");
        Serial.println(clPrint.getClusterAmount());
        for (clt::type_clAmount i = 0; i < clPrint.getClusterAmount(); i++) {
            Serial.print("["); Serial.print(i); Serial.print("]"); Serial.print(" Length: "); Serial.println(clPrint[i].length());
            for (clt::type_elemAmount j = 0; j < clPrint[i].length(); j++) {
                Serial.print(clPrint[i].getValue(j).toString());
            }
        }
    } else {
        Serial.println("[!] Empty cluster.");
    }
}

struct Color {
    const char* m_colorName;
    int m_colorId;

    Color(const char* colorName, int colorId)
        : m_colorName{colorName}, m_colorId{colorId}
    {}

    String toString() const { 
        return String("Color name: " + (String)m_colorName + "\n"
                      "Color ID:   " + m_colorId           + "\n\n");
    }
};

void setup() {
  Serial.begin(9600);
  
  const Color color[] = {
          {"Yellow", 4},
          {"Yellow", 4},
          {"Yellow", 4},
          {"Yellow", 4},
          {"Red", 10},
          {"Red", 10},
          {"Red", 10},
          {"Blue", 15},
          {"Blue", 15},
          {"Blue", 15}
  };
  const size_t arrayLength = sizeof(color) / sizeof(Color);
  
  Cluster<const Color> colorCl(&color[0], &color[arrayLength]);
  colorCl.insert(4);
  colorCl.insert(7);
  printCluster(colorCl);
}

void loop() {}
