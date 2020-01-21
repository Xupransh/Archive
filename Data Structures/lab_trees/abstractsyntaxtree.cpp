#include "abstractsyntaxtree.h"

bool isOp(std::string s) {
    if ((s).find_first_of("+*-/") != std::string::npos) {
        return true;
    }
    return false;
}

double AbstractSyntaxTree::evalRecurse(Node * treeNode) const {
    if (treeNode->elem == "+") {
        bool rightOp = isOp(treeNode->right->elem);
        bool leftOp = isOp(treeNode->left->elem);
        if(rightOp && leftOp) {
            return evalRecurse(treeNode->right) + evalRecurse(treeNode->left);
        } else if (rightOp) {
            return std::stod(treeNode->left->elem) + evalRecurse(treeNode->right);
        } else if (leftOp) {
            return std::stod(treeNode->right->elem) + evalRecurse(treeNode->left);
        } else {
            return  std::stod(treeNode->left->elem) + std::stod(treeNode->right->elem);
        }
    } else if (treeNode->elem == "*") {
        bool rightOp = isOp(treeNode->right->elem);
        bool leftOp = isOp(treeNode->left->elem);
        if(rightOp && leftOp) {
            return evalRecurse(treeNode->right) * evalRecurse(treeNode->left);
        } else if (rightOp) {
            return std::stod(treeNode->left->elem) * evalRecurse(treeNode->right);
        } else if (leftOp) {
            return std::stod(treeNode->right->elem) * evalRecurse(treeNode->left);
        } else {
            return  std::stod(treeNode->left->elem) * std::stod(treeNode->right->elem);
        }
    } else if (treeNode->elem == "/") {
        bool rightOp = isOp(treeNode->right->elem);
        bool leftOp = isOp(treeNode->left->elem);
        if(rightOp && leftOp) {
            return evalRecurse(treeNode->left) / evalRecurse(treeNode->right);
        } else if (rightOp) {
            return std::stod(treeNode->left->elem) / evalRecurse(treeNode->right);
        } else if (leftOp) {
            return evalRecurse(treeNode->left) / std::stod(treeNode->right->elem);
        } else {
            return  std::stod(treeNode->left->elem) / std::stod(treeNode->right->elem);
        }
    } else if (treeNode->elem == "-") {
        bool rightOp = isOp(treeNode->right->elem);
        bool leftOp = isOp(treeNode->left->elem);
        if(rightOp && leftOp) {
            return evalRecurse(treeNode->left) - evalRecurse(treeNode->right);
        } else if (rightOp) {
            return std::stod(treeNode->left->elem) - evalRecurse(treeNode->right);
        } else if (leftOp) {
            return - std::stod(treeNode->right->elem) + evalRecurse(treeNode->left);
        } else {
            return  std::stod(treeNode->left->elem) - std::stod(treeNode->right->elem);
        }
    }
    return std::stod(treeNode->elem);
}

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return evalRecurse(root);
}

