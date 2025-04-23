#include <iostream>  
using namespace std;

// Structure for an AVL Node
struct Player {
    int player_id;   // Unique player ID
    int score;       // Player's score (used as key)
    Player* left;    // Left child
    Player* right;   // Right child
    int height;      // Height of the node for balancing
};

// Function to get height of a node
int getHeight(Player* node) {
    if(node==nullptr)
        return 0;
    return(node->height);
}

// Function to create a new Player node
Player* createPlayer(int player_id, int score) {
    Player* newPlayer = new Player();
    newPlayer->player_id = player_id;
    newPlayer->score = score;
    newPlayer->left = newPlayer->right = nullptr;
    newPlayer->height = 1;
    return newPlayer;
}

// Function to get the balance factor
int getBalance(Player* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Right Rotate function (for balancing AVL tree)
Player* rightRotate(Player* y) {
    Player* x = y->left;
    Player* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left Rotate function (for balancing AVL tree)
Player* leftRotate(Player* x) {
    Player* y = x->right;
    Player* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Function to insert a player into the AVL tree
Player* insert(Player* root, int player_id, int score) {
    if (root == nullptr) {
        return createPlayer(player_id, score);
    }

    if (score < root->score) {
        root->left = insert(root->left, player_id, score);
    } else if (score > root->score) {
        root->right = insert(root->right, player_id, score);
    } else {
        return root;  // Duplicate scores are not allowed
    }

    // Update height of the current node
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // Get the balance factor
    int balance = getBalance(root);

    // Perform AVL rotations if necessary
    if (balance > 1 && score < root->left->score) {
        return rightRotate(root);
    }
    if (balance < -1 && score > root->right->score) {
        return leftRotate(root);
    }
    if (balance > 1 && score > root->left->score) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && score < root->right->score) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the minimum node in AVL tree (used for deletion)
Player* findMin(Player* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Function to delete a player from the AVL tree
Player* deletePlayer(Player* root, int score) {
    if (root == nullptr) {
        return root;
    }

    if (score < root->score) {
        root->left = deletePlayer(root->left, score);
    } else if (score > root->score) {
        root->right = deletePlayer(root->right, score);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Player* temp = (root->left != nullptr) ? root->left : root->right;
            delete root;
            return temp;
        }

        Player* temp = findMin(root->right);
        root->player_id = temp->player_id;
        root->score = temp->score;
        root->right = deletePlayer(root->right, temp->score);
    }

    
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to display the leaderboard (Inorder Traversal)
void displayLeaderboard(Player* root) {
    if (root != nullptr) {
        displayLeaderboard(root->left); // Higher scores first
        cout << "Player ID: " << root->player_id << " | Score: " << root->score << endl;
        displayLeaderboard(root->right);
    }
}

// Main function to demonstrate game system operations
int main() {
    Player* root = nullptr;

    // Register players
    root = insert(root, 101, 50);
    root = insert(root, 102, 70);
    root = insert(root, 103, 30);
    root = insert(root, 104, 90);
    root = insert(root, 105, 60);
    root = insert(root,106,91);

    cout << "\nLeaderboard:\n";
    displayLeaderboard(root);

    // Remove a player
    cout << "\nRemoving player with score 50...\n";
    root = deletePlayer(root, 50);
    
    cout << "\nUpdated Leaderboard:\n";
    displayLeaderboard(root);

    return 0;
}
