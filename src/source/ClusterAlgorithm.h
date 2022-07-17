#ifndef CLUSTERLIST_CLUSTERALGORITHM_H
#define CLUSTERLIST_CLUSTERALGORITHM_H

#include "Cluster.h"

#if IS_ARDUINO_FRAMEWORK == 1
    #include <ArxTypeTraits.h>
    #define enable_if enable_if
#else
    #define enable_if std::enable_if
#endif

template<class CL, typename T = CL>
class ClusterAlgorithm {
private:
    template <typename P>
    class has_comparator {
    private:
        typedef char enable[1];
        typedef char disable[2];
    private:
        template <typename C> static enable& check(decltype(&C::getComparator));
        template <typename C> static disable& check(...);
    public:
        enum { value = sizeof(check<P>(0)) == sizeof(enable) };
    };
private:
    Cluster<CL>& m_cl;
private:
    template<typename CL1 = CL>
    typename enable_if<!has_comparator<CL1>::value, T>::type getValue(clt::type_elemAmount i) const {
        return *(&m_cl[0] + i);
    }

    template<typename CL1 = CL>
    typename enable_if<has_comparator<CL1>::value, T>::type getValue(clt::type_elemAmount i) const {
        return (&m_cl[0] + i)->getComparator();
    }

    bool isContain(const clt::type_clAmount*, clt::type_clAmount, clt::type_clAmount) const;
    clt::type_clAmount* getIndexOfFirstKMax(clt::type_clAmount) const;
public:
    ClusterAlgorithm() = delete;
    ClusterAlgorithm(const ClusterAlgorithm&) = delete;
    ClusterAlgorithm& operator =(const ClusterAlgorithm&) = delete;
    ClusterAlgorithm(Cluster<CL>& cl)
            : m_cl{cl}
    {}

    void separateByDiff(clt::type_clAmount);
};


//----------[PUBLIC]
template<typename CL, class T>
void ClusterAlgorithm<CL, T>::separateByDiff(clt::type_clAmount clNum) {
    if(clNum < m_cl.length()) {
        auto *aBorders = getIndexOfFirstKMax(clNum);
        for (clt::type_clAmount i = 0; i < clNum; i++)
            m_cl.insert(aBorders[i] + 1); // noexcept function | +1 - наступний елемент є границею
        delete[] aBorders;
    }
}
//----------[PRIVATE]
template<typename CL, class T>
clt::type_clAmount* ClusterAlgorithm<CL, T>::getIndexOfFirstKMax(clt::type_clAmount k) const {
    auto* output = new clt::type_clAmount[k];
    output[0] = 0;

    for (int i = 0; i < k; i++) {
        auto maxIndex = 0, max = getValue(0) - 0;
        for (int j = 1; j < m_cl.length() - 2; j++) {
            const auto diff = getValue(j + 1) - getValue(j);
            if (max < diff && !isContain(output, i, j)) {
                max = diff;
                maxIndex = j;
            }
        }
        output[i] = maxIndex;
    }

    return output;
}

template<typename CL, class T>
bool ClusterAlgorithm<CL, T>::isContain(const clt::type_clAmount *haystack, clt::type_clAmount haystack_length, clt::type_clAmount needle) const {
    for(int i = 0; i < haystack_length; i++)
        if(haystack[i] == needle)
            return true;
    return false;
}

#endif //CLUSTERLIST_CLUSTERALGORITHM_H
