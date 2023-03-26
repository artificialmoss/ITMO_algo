#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class mem_block {
public:
    unsigned int offset;
    unsigned int size;
    bool is_free;
    struct mem_block* next;
};

void print_block(mem_block* block) {
    if (!block) {
        cout << "NO";
        return;
    }
    cout << '[' << block->offset << (block->is_free ? ".." : "||") << block->size + block->offset - 1 << ']';
}

void print_state(mem_block* head) {
    while (head) {
        print_block(head);
        head = head->next;
    }
}

void merge_blocks(mem_block* block) {
    while (block && block->next && block->is_free && block->next->is_free) {
        block->size = block->size + block->next->size;
        block->next = block->next->next;
    }
}

inline void split_blocks(mem_block* block, unsigned int req) {
    if (req == block->size) {
        return;
    }
    mem_block new_block = mem_block {
            .offset = block->offset + req,
            .size = block->size - req,
            .is_free = true,
            .next = block->next
    };
    block->next = &new_block;
    block->size = req;
}

mem_block* find_block(mem_block* head, unsigned int size) {
    while (head) {
        if (head->is_free && head->size >= size) {
            /*cout << "found:";
            print_block(head);
            cout << endl;*/
            return head;
        }
        head = head->next;
    }
    return nullptr;
}

int main() {
    unsigned int n, m;
    cin >> n >> m;
    mem_block memory = {
            .offset = 1,
            .size = n,
            .is_free = true,
            .next = nullptr
    };
    vector<mem_block> history;
    vector<mem_block> free_blocks = vector<mem_block>();
    history.resize(m + 1);
    string line;
    unsigned int req;
    mem_block* resp;
    for (int i = 1; i <= m; i++) {
        cin >> line;
        if (line[0] == '-') {
            req = stoi(line.substr(1));
            history[req].is_free = true;
            mem_block* head = &memory;
            while (head) {
                merge_blocks(head);
                head = head->next;
            }
            cout << req;
            print_block(&history[req]);
            cout << endl;
            print_state(&memory);
            cout <<endl << endl;
        } else {
            req = stoi(line);
            resp = find_block(&memory, req);

            if (resp) {
                history.at(i) = *resp;
                if (req < history.at(i).size) {
                    free_blocks.push_back({
                            .offset = history.at(i).offset + req,
                            .size = history.at(i).size - req,
                            .is_free = true,
                            .next = history.at(i).next
                    });
                    history.at(i).next = &free_blocks.back();
                    history.at(i).size = req;
                }
                history.at(i).is_free = false;
                print_block(&history.at(i));
                cout << endl;
                print_state(&memory);
                cout <<endl << endl;

                cout << "\t" << resp->offset << endl;
            } else {
                cout << "\t" << -1 << endl;
            }
        }
    }
}