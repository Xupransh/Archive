/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;


template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * Builds 2 points from the given point and dimension,
     * if new points are equal, it returns true if original first
     * point is smaller than original second point.
     */
    Point<1> first_cur(first[curDim]);
    Point<1> second_cur(second[curDim]);
    if (first_cur == second_cur) {
        return first < second;
    }

    /**
    * else returns true if co-ordinate of given dimension in first point
    * is lesser than the second point.
    */
    return first_cur < second_cur;
}

template <int Dim>
double KDTree<Dim>::distance (const Point <Dim> & first,
                              const Point<Dim> & second) const
{
    double dist = 0;
    for (int i = 0; i < Dim; i++) {
        dist += pow((first[i]-second[i]), 2);
    }
    return dist;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * Iterates through the points, setting the distances. If distances are
     * equal, return true if potential is smaller than currentBest.
     */
    double current_dist = distance(target, currentBest);
    double potential_dist = distance(target, potential);
    if (potential_dist == current_dist) {
        return potential < currentBest;
    }
    return potential_dist < current_dist;
}


template <int Dim>
int KDTree<Dim>::selectMedian(vector< Point<Dim> > & newPoints,
                              int dimension, int low, int high, int median_index)
{
    if (low == high) {
        return low;
    }
    int pivot_index = partition(newPoints, dimension, low, high, median_index);
    if (pivot_index == median_index) {
        return pivot_index;
    } else if (median_index < pivot_index) {
        return (selectMedian(newPoints, dimension, low, pivot_index-1, median_index));
    }
    return (selectMedian(newPoints, dimension, pivot_index+1, high, median_index));
}

template <int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & newPoints,
                           int dimension, int low, int high, int pivot_index)
{
    Point<Dim> temp = newPoints[pivot_index];
    newPoints[pivot_index] = newPoints[high];
    newPoints[high] = temp;
    int store_index = low;

    for (int i = low; i < high; i++) {
        if (smallerDimVal(newPoints[i], temp, dimension) || newPoints[i] == temp) {
            Point<Dim> another_temp = newPoints[store_index];
            newPoints[store_index] = newPoints[i];
            newPoints[i] = another_temp;
            store_index++;
        }
    }

    Point<Dim> swap_temp  = newPoints[high];
    newPoints[high] = newPoints[store_index];
    newPoints[store_index] = swap_temp;

    return store_index;
}



template <int Dim>
typename KDTree<Dim>::KDTreeNode*
KDTree<Dim>::KDTreeHelper(vector< Point<Dim> > & newPoints,
                          int dimension, int low, int high)
{
    if (high < low) {
        return NULL;
    }
    int median_index = (high-low)/2 + low;
    int mid = selectMedian(newPoints, dimension, low, high, median_index);
    KDTreeNode* node = new KDTreeNode(newPoints[mid]);
    node->left = KDTreeHelper(newPoints, (dimension+1)%Dim, low, mid-1);
    node->right = KDTreeHelper(newPoints, (dimension+1)%Dim, mid+1, high);
    return node;
}


template <int Dim>
void KDTree<Dim>::copyTree(KDTreeNode *& curr, KDTreeNode *& other) {
    if (other) {
        curr = new KDTreeNode(other->point);
        copyTree(curr->right, other->right);
        copyTree(curr->left, other->left);
    }
}

template <int Dim>
void KDTree<Dim>::copy(const KDTree<Dim>& other) {
    size = other.size;
    copyTree(root, other.root);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> >& newPoints)
{
    /**
     * start with dimension 0, find the median
     */
    int dimension = 0;
    int low = 0;
    int high = newPoints.size()-1;
    vector< Point<Dim> > copy_points(newPoints.begin(), newPoints.end());
    if (high != -1) {
        root = KDTreeHelper(copy_points, dimension, low, high);
    } else {
        root = NULL;
    }

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other)
{
  /**
   * @todo Implement this function!
   */
    copy(other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs)
{
    /**
     * @todo Implement this function!
     */

    if (*this != rhs) {
        clear(this);
        copy(rhs);
    }
    return *this;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * curr)
{
    if (curr) {
        clear(curr->right);
        clear(curr->left);
        delete(curr);
    }
}

template <int Dim>
KDTree<Dim>::~KDTree()
{
  /**
   * Simple recursive destructor
   */
    clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::NearestNeighborRecurse(KDTreeNode * curr, int dimension,
                                                const Point <Dim> & query,
                                                Point <Dim> best) const
{
    Point<Dim> potential = best;
    bool right = false;
    if (!curr->right && !curr->left) {
        if (shouldReplace(query, best, curr->point)) {
            return curr->point;
        }
        return best;
    } if (smallerDimVal(query, curr->point, dimension)) {
        if (curr->left) {
            potential = NearestNeighborRecurse(curr->left, (dimension+1)%Dim,
                                               query, best);
        }
    } else {
        if (curr->right) {
            potential = NearestNeighborRecurse(curr->right, (dimension+1)%Dim,
                                               query, best);
            right = true;
        }
    } if (shouldReplace(query, potential, curr->point)) {
        potential = curr->point;
    } if (pow((curr->point[dimension] - query[dimension]), 2) <= distance(query, potential)) {
        if (right && curr->left) {
            potential = NearestNeighborRecurse(curr->left, (dimension+1)%Dim,
                                               query, potential);
        } else if (!right && curr->right) {
            potential = NearestNeighborRecurse(curr->right, (dimension+1)%Dim,
                                               query, potential);
        }
    }
    return potential;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    KDTreeNode* curr = root;
    int dimension = 0;
    return NearestNeighborRecurse(root, dimension, query, root->point);
}
