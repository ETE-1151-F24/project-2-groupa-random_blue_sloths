#include <gtest/gtest.h>
#include "Inventory.hpp"

// Test fixture for Inventory tests
class InventoryTest : public ::testing::Test {
protected:
    void SetUp() override {
    

    void TearDown() override {
        
    }
};

// Test case for adding an item
TEST_F(InventoryTest, AddItem) {
    Inventory inventory;
    inventory.addItem("Healing Potion", "Restores 20 magic points.", 20);
    
    EXPECT_EQ(inventory.getItemCount(), 1);
}

// Test case for displaying inventory
TEST_F(InventoryTest, DisplayInventory) {
    Inventory inventory;
    inventory.addItem("Sword", "No magic bonus.", 0);
    
    testing::internal::CaptureStdout();
    inventory.display();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Sword") != std::string::npos);
}

// Main function for the test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}