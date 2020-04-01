#include <iostream>
#include <map>
#include <limits>

template<typename K, typename V>
class interval_map {
    std::map<K,V> m_map;
    typedef typename std::map<K,V>::iterator mapIterType;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }

    // Print interval map.
    void print_interval_map()
    {
        //typedef typename std::map<K,V>::iterator mapIterType;
        mapIterType mapIter = m_map.begin();
        while (mapIter != m_map.end()) {
            std::cout << mapIter->first << ':' << mapIter->second << '\n';
            mapIter++;
        }
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        if (keyBegin < keyEnd) {
            typedef typename std::map<K,V>::iterator mapIterationType;
            mapIterationType keyBeginIt, keyEndIt, nextIt, prevIt;

            prevIt = m_map.lower_bound(keyBegin);
            if (prevIt != m_map.begin()) {
                prevIt--;
            }
            nextIt = m_map.lower_bound(keyEnd);
            // For case when we haven't existed key in map.
            if (nextIt == m_map.end() || (nextIt != m_map.end() && keyEnd < (*nextIt).first)) {
                nextIt--;
            }

            if (m_map[(*prevIt).first] == val) {
                keyBeginIt = prevIt;
            }
            else {
                m_map.insert(m_map.end(),std::make_pair(keyBegin,val));
                keyBeginIt = m_map.find(keyBegin);
            }

            if (m_map[(*nextIt).first] == val) {
                keyEndIt = nextIt;
            }
            else {
                m_map.insert(m_map.end(),std::make_pair(keyEnd, m_map[(*nextIt).first]));
                keyEndIt = m_map.find(keyEnd);
            }

            // Clear all items in interval
            keyBeginIt++;
            if ((*keyBeginIt).first < (*keyEndIt).first) {
                m_map.erase(keyBeginIt, keyEndIt);
            }

            keyBeginIt--;
            if (keyBeginIt != keyEndIt && m_map[(*keyBeginIt).first] == m_map[(*keyEndIt).first]) {
                m_map.erase((*keyEndIt).first);
            }
        }
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};


int main() {
    std::cout << "Welcome to Interval realization program!" << std::endl << std::endl;

    // Initialize interval.
    interval_map<unsigned int,char> my_interval_map('a');

    // Print all initial interval map.
    my_interval_map.print_interval_map();

    std::cout << std::endl << "1: " << std::endl;
    my_interval_map.assign(2,4,'F');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "2: " << std::endl;
    my_interval_map.assign(1,3,'G');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "3: " << std::endl;
    my_interval_map.assign(2,5,'H');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "4: " << std::endl;
    my_interval_map.assign(3, 7,'H');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "5: " << std::endl;
    my_interval_map.assign(0, 6,'a');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "6: " << std::endl;
    my_interval_map.assign(1, 4, 'b');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "7: " << std::endl;
    my_interval_map.assign(2, 3, 'c');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "8: " << std::endl;
    my_interval_map.assign(std::numeric_limits<unsigned int>::min(), 5, 'a');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "9: " << std::endl;
    my_interval_map.assign(1, 2, 'a');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "10: " << std::endl;
    my_interval_map.assign(1, 3, 'b');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "11: " << std::endl;
    my_interval_map.assign(2, 4, 'a');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "12: " << std::endl;
    my_interval_map.assign(0, std::numeric_limits<unsigned int>::max() + 1, 'b');
    my_interval_map.print_interval_map();

    std::cout << std::endl << "13: " << std::endl;
    my_interval_map.assign(-4, 0, 'b');
    my_interval_map.print_interval_map();

    // Initialize interval.
    std::cout << std::endl << "NEW CHAR_DOUBLE: " << std::endl;
    interval_map<char,double> my_interval_map2(10.0);
    // Print all initial interval map.
    my_interval_map2.print_interval_map();

    std::cout << std::endl << "14: " << std::endl;
    my_interval_map2.assign(-128,'d',12.0);
    my_interval_map2.print_interval_map();

    std::cout << std::endl << "15: " << std::endl;
    my_interval_map2.assign('a','c',10);
    my_interval_map2.print_interval_map();

    return 0;
}