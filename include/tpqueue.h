#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
  private:
    struct Node {
      T data;
      Node* next;
      explicit Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head;

  public:
    TPQueue() : head(nullptr) {}
    ~TPQueue() {
      while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
      }
    }

    TPQueue(const TPQueue&) = delete;
    TPQueue& operator=(const TPQueue&) = delete;

    void push(const T& item) {
      Node* newNode = new Node(item);
      if (!head || item.prior > head->data.prior) {
        newNode->next = head;
        head = newNode;
        return;
      }
      Node* cur = head;
      while (cur->next && cur->next->data.prior >= item.prior) {
        cur = cur->next;
      }
      newNode->next = cur->next;
      cur->next = newNode;
    }

    T pop() {
      if (!head) throw std::runtime_error("pop from empty TPQueue");
      Node* tmp = head;
      T value = head->data;
      head = head->next;
      delete tmp;
      return value;
    }

    const T& top() const {
      if (!head) throw std::runtime_error("top from empty TPQueue");
      return head->data;
    }

    bool empty() const {
      return head == nullptr;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
