#include <iostream>
// corrected from the book


template <int ... N>
struct NumberList;

// Get Front Element
template <typename List>
struct FrontElementT;

template <int Head, int ... Tail>
struct FrontElementT<NumberList<Head, Tail...>> {
    static const int value = Head;
};

template <typename List>
static const int FrontElement = FrontElementT<List>::value;


// Pop Front
template <typename List>
struct PopFrontT;

template <int Head, int ... Tail>
struct PopFrontT<NumberList<Head, Tail...>> {
    using type = NumberList<Tail...>;
};

template <typename List>
using PopFront = typename PopFrontT<List>::type;



// Push Front
template <int Element, typename List>
struct PushFrontT;

template <int Element, int ... N>
struct PushFrontT<Element, NumberList<N...>> {
    using type = NumberList<Element, N...>;
};

template <int Element, typename List>
using PushFront = typename PushFrontT<Element, List>::type;

// Comparator function
template<int L, int R>
struct Less {
    static constexpr bool value = L < R;
};

// Partition Left
template <int Pivot, typename List, template <int, int> typename Compare>
struct PartitionLeftT;

template <int Pivot, int Head, int ... Tail, template<int, int> typename Compare>
struct PartitionLeftT<Pivot, NumberList<Head, Tail...>, Compare> {
    using type = typename std::conditional_t<Compare<Head, Pivot>::value,
                                             PushFront<Head, typename PartitionLeftT<Pivot, NumberList<Tail...>, Compare>::type>,
                                             typename PartitionLeftT<Pivot, NumberList<Tail...>, Compare>::type>;
};

template <int Pivot, template<int, int> typename Compare>
struct PartitionLeftT<Pivot, NumberList<>, Compare> {
    using type = NumberList<>;
};

template <int Pivot, typename List, template<int, int> typename Compare>
using PartitionLeft = typename PartitionLeftT<Pivot, List, Compare>::type;

// Partition Right
template <int Pivot, typename List, template<int, int> typename Compare>
struct PartitionRightT;

template <int Pivot, int Head, int ... Tail, template<int, int> typename Compare>
struct PartitionRightT<Pivot, NumberList<Head, Tail...>, Compare> {
    using type = typename std::conditional_t<!Compare<Head, Pivot>::value,
                                             PushFront<Head, typename PartitionRightT<Pivot, NumberList<Tail...>, Compare>::type>,
                                             typename PartitionRightT<Pivot, NumberList<Tail...>, Compare>::type>;
};

template <int Pivot, template<int, int> typename Compare>
struct PartitionRightT<Pivot, NumberList<>, Compare> {
    using type = NumberList<>;
};

template <int Pivot, typename List, template<int, int> typename Compare>
using PartitionRight = typename PartitionRightT<Pivot, List, Compare>::type;


// Concatenate
template <typename LList, int M, typename RList>
struct ConcatenateT;

template <int ... L, int M, int ... R>
struct ConcatenateT<NumberList<L...>, M, NumberList<R...>> {
    using type = NumberList<L..., M, R...>;
};
template <typename LList, int M, typename RList>
using Concatenate = typename ConcatenateT<LList, M, RList>::type;

// Quick sort
template <typename List, template<int, int> typename Compare>
struct QuickSortT {
    using Result = Concatenate<typename QuickSortT<PartitionLeft<FrontElement<List>, PopFront<List>, Compare>, Compare>::Result,
                               FrontElement<List>,
                               typename QuickSortT<PartitionRight<FrontElement<List>, PopFront<List>, Compare>, Compare>::Result>;
};

template <template<int, int> typename Compare>
struct QuickSortT<NumberList<>, Compare> {
    using Result = NumberList<>;
};

template <int N, template<int, int> typename Compare>
struct QuickSortT<NumberList<N>, Compare> {
    using Result = NumberList<N>;
};
template <typename List, template<int, int> typename Compare>
using QuickSort = typename QuickSortT<List, Compare>::Result;


// Helper function to print the NumberList
template <typename List>
void printList() {
    if constexpr (std::is_same_v<List, NumberList<>>) {
        std::cout << "(empty)";
    } else {
        // Extract elements recursively using a helper structure
        constexpr int firstElement = FrontElement<List>;
        using RestList = PopFront<List>;
        std::cout << firstElement << " ";
        printList<RestList>();
    }
}

int main() {
    // Define a NumberList
    using MyList = NumberList<3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5>;

    std::cout << "Original List: ";
    printList<MyList>();
    std::cout <<std::endl;

    // Test PushFront
    using ListAfterPush = PushFront<7, MyList>;
    std::cout << "After Pushing Front 7: ";
    printList<ListAfterPush>();
    std::cout <<std::endl;

    // Test PopFront
    using ListAfterPop = PopFront<MyList>;
    std::cout << "After Popping Front: ";
    printList<ListAfterPop>();
    std::cout <<std::endl;

    // Test QuickSort
    using SortedList = QuickSort<MyList, Less>;
    std::cout << "Sorted List: ";
    printList<SortedList>();
    std::cout <<std::endl;

    return 0;
}