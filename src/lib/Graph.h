//
// Created by pollini on 21/01/2022.
//

#ifndef RL_DA_ZERO_GRAPH_H
#define RL_DA_ZERO_GRAPH_H

#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Rng.h"

template <typename T>
class Graph {
   public:
    using ElementPtr = std::shared_ptr<T>;

    using Vertex = ElementPtr;

    struct Edge {
        ElementPtr to;
    };

    Graph() = default;

    explicit Graph(ElementPtr rootElement) : root_(rootElement) { addElement(rootElement); }

    ElementPtr getRandomElement() const {
        auto index = Rng::getInstance().getRandomInt(0, elements_.size() - 1);
        return elements_[index];
    }

    void addElement(ElementPtr element) {
        elements_.push_back(element);
        if (elements_.empty()) {
            root_ = elements_[0];
        }
    }

    ElementPtr& elementAt(int index) { return elements_[index]; }

    void addEdge(ElementPtr from, ElementPtr to) {
        if (from == to) {
            return;
        }
        // aggiungi gli elementi non esistenti
        if (std::find(elements_.begin(),elements_.end(),from) == elements_.end()) {
            addElement(from);
        }
        if (std::find(elements_.begin(),elements_.end(),to) == elements_.end()) {
            addElement(to);
        }
        // aggiungi l'edge
        if (edges_.contains(from)) {
            edges_[from].push_back({to});
        } else {
            edges_[from] = {{to}};
        }
    }

    std::vector<ElementPtr> elements() const { return elements_; }

//    bool roomOverlaps(ElementPtr room) const {
//        for (auto& element : elements_) {
//            if (element->overlaps(room)) {
//                return true;
//            }
//        }
//        return false;
//    }

   private:
    std::vector<ElementPtr> elements_;
    std::unordered_map<ElementPtr, std::vector<Edge>> edges_;
    ElementPtr root_;
};

#endif  // RL_DA_ZERO_GRAPH_H
