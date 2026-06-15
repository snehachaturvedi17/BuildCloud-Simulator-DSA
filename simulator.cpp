// BuildCloud Distributed Code Compilation Simulator
// A basic DSA project for tracking compilation steps

#include <iostream>
#include <string>

using namespace std;

#define MAX_SIZE 50

// --- 1. Package Tracker (BST) ---
struct TreeNode {
    string pkgName;
    TreeNode *left;
    TreeNode *right;
    
    TreeNode(string n) {
        pkgName = n;
        left = NULL;
        right = NULL;
    }
};

class PackageTree {
    TreeNode* root;

    TreeNode* insertNode(TreeNode* node, string val) {
        if (node == NULL) {
            return new TreeNode(val);
        }
        if (val < node->pkgName) {
            node->left = insertNode(node->left, val);
        } else if (val > node->pkgName) {
            node->right = insertNode(node->right, val);
        }
        return node;
    }

    void printInorder(TreeNode* node) {
        if (node == NULL) return;
        printInorder(node->left);
        cout << " -> " << node->pkgName << endl;
        printInorder(node->right);
    }

    bool searchTree(TreeNode* node, string val) {
        if (node == NULL) return false;
        if (node->pkgName == val) return true;
        
        if (val < node->pkgName) {
            return searchTree(node->left, val);
        } else {
            return searchTree(node->right, val);
        }
    }

public:
    PackageTree() {
        root = NULL;
    }

    void addPackage(string n) { 
        root = insertNode(root, n); 
        cout << "Package " << n << " added to tracker.\n"; 
    }
    
    // time complexity O(n)
    void showAll() { 
        if (root == NULL) {
            cout << "No packages yet.\n";
            return;
        }
        cout << "Packages (Sorted):\n"; 
        printInorder(root); 
    }
    
    void findPackage(string n) { 
        if(searchTree(root, n)) {
            cout << "Found package: " << n << endl;
        } else {
            cout << "Package not found!" << endl;
        }
    }
};

// --- 2. Build History (Stack using Array) ---
class HistoryStack {
    string history[MAX_SIZE];
    int topIndex;
public:
    HistoryStack() {
        topIndex = -1;
    }

    void pushHistory(string step) { 
        if(topIndex < MAX_SIZE - 1) { 
            topIndex++;
            history[topIndex] = step; 
            cout << "Saved to history: " << step << endl; 
        } else {
            cout << "History full!\n";
        }
    }
    
    // undo last operation
    void popHistory() { 
        if(topIndex >= 0) {
            cout << "Undoing step: " << history[topIndex] << endl; 
            topIndex--;
        } else {
            cout << "Nothing to undo.\n"; 
        }
    }
    
    void displayHistory() { 
        if (topIndex == -1) {
            cout << "History is empty\n";
            return;
        }
        cout << "Recent steps:\n";
        for(int i = topIndex; i >= 0; i--) {
            cout << "- " << history[i] << endl; 
        }
    }
};

// --- 3. Task Line (Queue using Array) ---
class JobQueue {
    string jobs[MAX_SIZE];
    int front, rear;
public:
    JobQueue() {
        front = 0;
        rear = 0;
    }

    void addJob(string t) { 
        if(rear < MAX_SIZE) { 
            jobs[rear] = t; 
            rear++;
            cout << "Job queued: " << t << endl; 
        } else {
            cout << "Queue is full\n";
        }
    }
    
    void processJob() { 
        if(front < rear) {
            cout << "Processing: " << jobs[front] << endl; 
            front++;
        } else {
            cout << "No jobs left in queue.\n"; 
        }
    }
    
    void showJobs() { 
        if (front == rear) {
            cout << "Queue empty\n";
            return;
        }
        cout << "Pending jobs:\n";
        for(int i = front; i < rear; i++) {
            cout << (i - front + 1) << ". " << jobs[i] << endl; 
        }
    }
};

// --- 4. File Finder (Binary Search) ---
class FileSearcher {
    string files[MAX_SIZE];
    int totalFiles;
public:
    FileSearcher() {
        totalFiles = 0;
    }

    void insertFile(string f) {
        if(totalFiles >= MAX_SIZE) {
            cout << "File limit reached\n";
            return;
        }
        
        // simple insertion sort to keep array sorted for binary search
        int i = totalFiles - 1;
        while(i >= 0 && files[i] > f) { 
            files[i+1] = files[i]; 
            i--; 
        }
        files[i+1] = f; 
        totalFiles++;
        
        cout << "File saved: " << f << endl;
    }
    
    // binary search logic (O(log n))
    void searchFile(string f) { 
        int left = 0;
        int right = totalFiles - 1;
        int flag = 0;
        
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(files[mid] == f) { 
                cout << f << " found at position " << mid + 1 << endl; 
                flag = 1;
                break; 
            }
            if(files[mid] < f) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        if (flag == 0) {
            cout << "File not found.\n";
        }
    }
};

// --- 5. Change Sorter (Merge Sort) ---
struct ModuleInfo { 
    string moduleName; 
    int noOfChanges; 
};

class ChangeSorter {
    ModuleInfo modules[MAX_SIZE];
    int modCount;

    void doMerge(int left, int mid, int right) {
        ModuleInfo tempArray[MAX_SIZE];
        int i = left;
        int j = mid + 1;
        int k = left;
        
        while(i <= mid && j <= right) {
            // sorting in descending order based on changes
            if(modules[i].noOfChanges >= modules[j].noOfChanges) {
                tempArray[k] = modules[i];
                i++;
            } else {
                tempArray[k] = modules[j];
                j++;
            }
            k++;
        }
        
        while(i <= mid) {
            tempArray[k] = modules[i];
            i++; k++;
        }
        while(j <= right) {
            tempArray[k] = modules[j];
            j++; k++;
        }
        
        // copy back
        for(int index = left; index <= right; index++) {
            modules[index] = tempArray[index];
        }
    }

    void doMergeSort(int left, int right) {
        if(left < right) {
            int mid = left + (right - left) / 2;
            doMergeSort(left, mid); 
            doMergeSort(mid + 1, right);
            doMerge(left, mid, right);
        }
    }

public:
    ChangeSorter() {
        modCount = 0;
    }

    void recordChanges(string n, int c) { 
        if(modCount < MAX_SIZE) {
            modules[modCount].moduleName = n;
            modules[modCount].noOfChanges = c;
            modCount++;
            cout << "Changes recorded.\n"; 
        } else {
            cout << "Tracker full\n";
        }
    }
    
    void sortAndDisplay() { 
        if (modCount == 0) {
            cout << "No data to sort\n";
            return;
        }
        doMergeSort(0, modCount - 1); 
        cout << "Modules by most changes:\n";
        for(int i = 0; i < modCount; i++) {
            cout << modules[i].moduleName << " -> " << modules[i].noOfChanges << " changes\n"; 
        }
    } 
};

// --- 6. Dependency Map (Graph DFS/BFS) ---
struct NodeEdge { 
    int destIndex; 
    NodeEdge* nextEdge; 
};

class GraphMap {
    NodeEdge* adjList[MAX_SIZE];
    string nodes[MAX_SIZE];
    int numNodes;
    
    int findIndex(string n) {
        for(int i = 0; i < numNodes; i++) {
            if(nodes[i] == n) return i;
        }
        nodes[numNodes] = n; 
        numNodes++;
        return numNodes - 1;
    }

    void dfsHelper(int v, bool visited[]) {
        visited[v] = true; 
        cout << nodes[v] << " ";
        
        NodeEdge* temp = adjList[v];
        while(temp != NULL) {
            if(visited[temp->destIndex] == false) {
                dfsHelper(temp->destIndex, visited);
            }
            temp = temp->nextEdge;
        }
    }

public:
    GraphMap() {
        numNodes = 0;
        for(int i = 0; i < MAX_SIZE; i++) {
            adjList[i] = NULL;
        }
    }

    void insertDep(string src, string dest) { 
        int u = findIndex(src);
        int v = findIndex(dest);
        
        NodeEdge* newNode = new NodeEdge;
        newNode->destIndex = v;
        newNode->nextEdge = adjList[u];
        adjList[u] = newNode;
        
        cout << src << " depends on " << dest << endl;
    }
    
    void printDFS(string startPoint) { 
        bool visited[MAX_SIZE];
        for(int i = 0; i < MAX_SIZE; i++) visited[i] = false;
        
        int startIdx = findIndex(startPoint);
        cout << "DFS output: "; 
        dfsHelper(startIdx, visited); 
        cout << endl;
    }
    
    void printBFS(string startPoint) { 
        bool visited[MAX_SIZE];
        for(int i = 0; i < MAX_SIZE; i++) visited[i] = false;
        
        int queueArr[MAX_SIZE];
        int front = 0, rear = 0;
        
        int startIdx = findIndex(startPoint);
        visited[startIdx] = true; 
        queueArr[rear++] = startIdx;
        
        cout << "BFS output: ";
        while(front < rear) {
            int current = queueArr[front++]; 
            cout << nodes[current] << " ";
            
            NodeEdge* temp = adjList[current];
            while(temp != NULL) {
                if(visited[temp->destIndex] == false) { 
                    visited[temp->destIndex] = true; 
                    queueArr[rear++] = temp->destIndex; 
                }
                temp = temp->nextEdge;
            }
        }
        cout << endl;
    }
};

// --- 7. Fastest Build (Dijkstra Algorithm) ---
class BuildPath {
    int adjMatrix[MAX_SIZE][MAX_SIZE];
    string modNames[MAX_SIZE];
    int count;

    int getModuleIndex(string n) {
        for(int i = 0; i < count; i++) {
            if(modNames[i] == n) return i;
        }
        modNames[count] = n; 
        count++;
        return count - 1;
    }
public:
    BuildPath() {
        count = 0;
        for(int i = 0; i < MAX_SIZE; i++) {
            for(int j = 0; j < MAX_SIZE; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addConnection(string u, string v, int weight) { 
        int idx1 = getModuleIndex(u);
        int idx2 = getModuleIndex(v);
        adjMatrix[idx1][idx2] = weight; 
        cout << "Path time added.\n";
    }
    
    void findShortestTime(string start) { 
        int distances[MAX_SIZE]; 
        bool isDone[MAX_SIZE];
        
        for(int i = 0; i < count; i++) {
            distances[i] = 99999; // treating 99999 as infinity
            isDone[i] = false;
        }
        
        int startIdx = getModuleIndex(start);
        distances[startIdx] = 0;

        for(int i = 0; i < count - 1; i++) {
            int minVal = 99999;
            int minIndex = -1;
            
            // find min distance node
            for(int j = 0; j < count; j++) {
                if(isDone[j] == false && distances[j] < minVal) { 
                    minVal = distances[j]; 
                    minIndex = j; 
                }
            }
            
            if(minIndex == -1) break; // no more reachable nodes
            
            isDone[minIndex] = true;
            
            // update neighbours
            for(int v = 0; v < count; v++) {
                if(isDone[v] == false && adjMatrix[minIndex][v] != 0) {
                    if (distances[minIndex] + adjMatrix[minIndex][v] < distances[v]) {
                        distances[v] = distances[minIndex] + adjMatrix[minIndex][v];
                    }
                }
            }
        }
        
        cout << "Shortest build times from " << start << ":\n";
        for(int i = 0; i < count; i++) {
            cout << modNames[i] << ": ";
            if (distances[i] == 99999) {
                cout << "Not reachable\n";
            } else {
                cout << distances[i] << " seconds\n";
            }
        }
    }
};

// --- 8. Memory Manager (Greedy Approach) ---
class MemoryAllocator {
    int memoryBlocks[MAX_SIZE];
    bool isBlockAllocated[MAX_SIZE];
    int blockCount;
public:
    MemoryAllocator() {
        blockCount = 0;
        for(int i = 0; i < MAX_SIZE; i++) {
            isBlockAllocated[i] = false;
        }
    }

    void addMemBlock(int size) { 
        if (blockCount < MAX_SIZE) {
            memoryBlocks[blockCount] = size; 
            blockCount++;
            cout << "Added memory block of size " << size << "MB.\n"; 
        }
    }
    
    // simple greedy first-fit allocation
    void giveMemory(string module, int requiredSize) { 
        int flag = 0;
        for(int i = 0; i < blockCount; i++) {
            if(isBlockAllocated[i] == false && memoryBlocks[i] >= requiredSize) { 
                isBlockAllocated[i] = true; 
                cout << "Allocated " << module << " to Block " << (i + 1) << " (" << memoryBlocks[i] << "MB)\n"; 
                flag = 1;
                break; 
            }
        }
        
        if (flag == 0) {
            cout << "Error: Not enough contiguous memory for " << module << "!\n";
        }
    }
};

// main menu display
void printMenu() {
    cout << "\n----------------------------------------\n";
    cout << " BuildCloud Compiler Simulator Menu\n";
    cout << "----------------------------------------\n";
    cout << " 1. Package Tracker (BST)\n";
    cout << " 2. Build History (Stack)\n";
    cout << " 3. Task Line (Queue)\n";
    cout << " 4. File Finder (Binary Search)\n";
    cout << " 5. Change Sorter (Merge Sort)\n";
    cout << " 6. Dependency Map (Graph Traversal)\n";
    cout << " 7. Fastest Build Path (Dijkstra)\n";
    cout << " 8. Memory Manager (Greedy)\n";
    cout << " 9. Exit Program\n";
    cout << "----------------------------------------\n";
    cout << "Enter your choice: ";
}

int main() {
    // objects for all modules
    PackageTree pTree; 
    HistoryStack hStack; 
    JobQueue jQueue; 
    FileSearcher fSearcher;
    ChangeSorter cSorter; 
    GraphMap gMap; 
    BuildPath bPath; 
    MemoryAllocator mAlloc;
    
    int userChoice;
    int option;
    string input1, input2;
    int numInput;
    
    do {
        printMenu();
        cin >> userChoice;
        
        if (userChoice == 1) {
            cout << "1. Add Package\n2. Search\n3. Display All\nSelect option: ";
            cin >> option;
            if (option == 1) {
                cout << "Enter package name: ";
                cin >> input1;
                pTree.addPackage(input1);
            } else if (option == 2) {
                cout << "Enter name to search: ";
                cin >> input1;
                pTree.findPackage(input1);
            } else {
                pTree.showAll();
            }
        } 
        else if (userChoice == 2) {
            cout << "1. Record Step\n2. Undo\n3. View History\nSelect option: ";
            cin >> option;
            if (option == 1) {
                cout << "Enter command/step: ";
                cin >> input1;
                hStack.pushHistory(input1);
            } else if (option == 2) {
                hStack.popHistory();
            } else {
                hStack.displayHistory();
            }
        }
        else if (userChoice == 3) {
            cout << "1. Add Job\n2. Process Next\n3. Show Queue\nSelect option: ";
            cin >> option;
            if (option == 1) {
                cout << "Enter job name: ";
                cin >> input1;
                jQueue.addJob(input1);
            } else if (option == 2) {
                jQueue.processJob();
            } else {
                jQueue.showJobs();
            }
        }
        else if (userChoice == 4) {
            cout << "1. Add File\n2. Binary Search File\nSelect option: ";
            cin >> option;
            if (option == 1) {
                cout << "Enter filename: ";
                cin >> input1;
                fSearcher.insertFile(input1);
            } else if (option == 2) {
                cout << "Enter filename to search: ";
                cin >> input1;
                fSearcher.searchFile(input1);
            }
        }
        else if (userChoice == 5) {
            cout << "1. Record Module Changes\n2. Sort & View\nSelect option: ";
            cin >> option;
            if (option == 1) {
                cout << "Module name: ";
                cin >> input1;
                cout << "Number of changes: ";
                cin >> numInput;
                cSorter.recordChanges(input1, numInput);
            } else {
                cSorter.sortAndDisplay();
            }
        }
        else if (userChoice == 6) {
            cout << "1. Add Edge\n2. Run DFS\n3. Run BFS\nSelect option: ";
            cin >> option;
            if (option == 1) {
                cout << "Source module: ";
                cin >> input1;
                cout << "Destination module: ";
                cin >> input2;
                gMap.insertDep(input1, input2);
            } else if (option == 2) {
                cout << "Start node for DFS: ";
                cin >> input1;
                gMap.printDFS(input1);
            } else {
                cout << "Start node for BFS: ";
                cin >> input1;
                gMap.printBFS(input1);
            }
        }
        else if (userChoice == 7) {
            cout << "1. Add Compilation Path\n2. Calculate Shortest Time\nSelect option: ";
            cin >> option;
            if (option == 1) {
                cout << "From: ";
                cin >> input1;
                cout << "To: ";
                cin >> input2;
                cout << "Time (seconds): ";
                cin >> numInput;
                bPath.addConnection(input1, input2, numInput);
            } else {
                cout << "Start module: ";
                cin >> input1;
                bPath.findShortestTime(input1);
            }
        }
        else if (userChoice == 8) {
            cout << "1. Create Memory Block\n2. Allocate Memory\nSelect option: ";
            cin >> option;
            if (option == 1) {
                cout << "Block size (MB): ";
                cin >> numInput;
                mAlloc.addMemBlock(numInput);
            } else {
                cout << "Module name: ";
                cin >> input1;
                cout << "Required size (MB): ";
                cin >> numInput;
                mAlloc.giveMemory(input1, numInput);
            }
        }
        else if (userChoice == 9) {
            cout << "Exiting simulator...\n";
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
        
    } while (userChoice != 9);

    return 0;
}
