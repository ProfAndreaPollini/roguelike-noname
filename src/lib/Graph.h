//
// Created by pollini on 21/01/2022.
//

#ifndef RL_DA_ZERO_GRAPH_H
#define RL_DA_ZERO_GRAPH_H

#include <algorithm>
#include <array>
#include <functional>
#include <iterator>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Rng.h"

template <typename T>
struct [[maybe_unused]] DirectedEdge {
    T to;
};

/*
 *
 * struct Edge {
ElementPtr to;
};
 */

template <typename T, typename E = DirectedEdge<T>>
class Graph {
   public:
    using ElementPtr = T;

    using Vertex = ElementPtr;
    using Edge = E;

    Graph() = default;

    explicit Graph(ElementPtr rootElement) : root_(rootElement) {
        addElement(rootElement);
    }

    auto getRandomElement() const -> ElementPtr {
        auto index = Rng::getInstance().getRandomInt(0, elements_.size() - 1);
        return elements_[index];
    }

    virtual void addElement(ElementPtr element) {
        elements_.push_back(element);
        if (elements_.empty()) {
            root_ = elements_[0];
        }
    }

    auto elementAt(int index) -> ElementPtr& { return elements_[index]; }

    virtual void addEdge(ElementPtr elementFrom, ElementPtr elementTo) {
        if (elementFrom == elementTo) {
            return;
        }
        // aggiungi gli elementi non esistenti
        if (std::find(elements_.begin(), elements_.end(), elementFrom) ==
            elements_.end()) {
            addElement(elementFrom);
        }
        if (std::find(elements_.begin(), elements_.end(), elementTo) ==
            elements_.end()) {
            addElement(elementTo);
        }
        // aggiungi l'edge
        if (edges_.contains(elementFrom)) {
            edges_[elementFrom].push_back({elementTo});
        } else {
            edges_[elementFrom] = {{elementTo}};
        }
    }

    std::vector<ElementPtr> getNeighbors(ElementPtr element) const {
        std::vector<ElementPtr> neighbors;
        if (edges_.contains(element)) {
            for (const auto& edge : edges_.at(element)) {
                neighbors.push_back(edge.to);
            }
        }
        return neighbors;
    }

    auto elements() const -> std::vector<ElementPtr> { return elements_; }

    std::vector<int> BFS() {
        std::vector<int> ret;
        // Mark all the vertices as not visited
        bool visited[elements_.size()];
        for (int i = 0; i < elements_.size(); i++) visited[i] = false;

        // Create a queue for BFS
        std::list<int> queue;

        // Mark the current node as visited and enqueue it
        visited[0] = true;
        queue.push_back(0);

        while (!queue.empty()) {
            // Dequeue a vertex from queue and print it
            auto s = queue.front();
            //            spdlog::info("{}", s);
            ret.push_back(s);
            queue.pop_front();

            auto currentElement = elements_[s];
            const auto& connectedElements = getNeighbors(currentElement);

            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            for (const auto& connectedElement : connectedElements) {
                auto elementIdx = std::find(elements_.begin(), elements_.end(),
                                            connectedElement);
                auto elementPos = std::distance(elements_.begin(), elementIdx);

                if (!visited[elementPos]) {
                    visited[elementPos] = true;
                    queue.push_back(elementPos);
                }
            }
        }
        return ret;
    }

   private:
    std::vector<ElementPtr> elements_;
    std::unordered_map<ElementPtr, std::vector<Edge>> edges_;
    ElementPtr root_;
};

template <typename T>
class LatticeGraph : public Graph<T> {
   public:
    LatticeGraph() = default;
    [[maybe_unused]] explicit LatticeGraph(typename Graph<T>::ElementPtr root)
        : Graph<T>(root) {}

    void addEdge(typename Graph<T>::ElementPtr elementFrom,
                 typename Graph<T>::ElementPtr elementTo) override {
        Graph::addEdge(elementFrom, elementTo);
        Graph::addEdge(elementTo, elementFrom);
    }
};

template <typename T, typename DATA>
class LatticeGraphWithData : public LatticeGraph<T> {
   public:
    LatticeGraphWithData() = default;
    [[maybe_unused]] explicit LatticeGraphWithData(
        typename Graph<T>::ElementPtr root)
        : LatticeGraph<T>(root) {}

    void addElement(typename Graph<T>::ElementPtr element, DATA data) override {
        Graph::addElement(element);
        data_.push_back(data);
    }

   private:
    std::unordered_map<T, DATA> data_;
};

#endif  // RL_DA_ZERO_GRAPH_H
