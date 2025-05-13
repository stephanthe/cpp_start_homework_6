#include "../libs/serial_container.hpp"

#include <gtest/gtest.h>


TEST(SerialContainer, DefaultConstructor) {
    // Arrange
    my::SerialContainer<int> container;

    // Act (empty for this test)

    // Assert
    EXPECT_EQ(container.size(), 0);
    EXPECT_EQ(container.capacity(), 10); // initial_capacity = 10
}

TEST(SerialContainer, InitializerListConstructor) {
    // Arrange & Act
    my::SerialContainer<int> container = {1, 2, 3, 4, 5};

    // Assert
    ASSERT_EQ(container.size(), 5);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 3);
    EXPECT_EQ(container[3], 4);
    EXPECT_EQ(container[4], 5);
}

TEST(SerialContainer, CopyConstructor) {
    // Arrange
    my::SerialContainer<int> original = {1, 2, 3, 4, 5};

    // Act
    my::SerialContainer<int> copy = original;

    // Assert
    ASSERT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy[0], original[0]);
    EXPECT_EQ(copy[1], original[1]);
    EXPECT_EQ(copy[2], original[2]);
    EXPECT_EQ(copy[3], original[3]);
    EXPECT_EQ(copy[4], original[4]);

    // Check that modifying the copy does not affect the original
    copy.push_back(6);
    ASSERT_NE(copy.size(), original.size());
}

TEST(SerialContainer, CopyAssignmentOperator) {
    // Arrange
    my::SerialContainer<int> original = {1, 2, 3, 4, 5};
    my::SerialContainer<int> copy;

    // Act
    copy = original;
    
    // Assert
    ASSERT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy[0], original[0]);
    EXPECT_EQ(copy[1], original[1]);
    EXPECT_EQ(copy[2], original[2]);
    EXPECT_EQ(copy[3], original[3]);
    EXPECT_EQ(copy[4], original[4]);
    
    copy.push_back(6);
    ASSERT_NE(copy.size(), original.size());
}

TEST(SerialContainer, MoveConstructor) {
    // Arrange
    my::SerialContainer<int> original = {1, 2, 3, 4, 5};

    // Act
    my::SerialContainer<int> moved = std::move(original);

    // Assert
    ASSERT_EQ(moved.size(), 5);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);
    EXPECT_EQ(moved[3], 4);
    EXPECT_EQ(moved[4], 5);
    ASSERT_EQ(original.size(), 0);
}

TEST(SerialContainer, MoveAssignmentOperator) {
    // Arrange
    my::SerialContainer<int> original = {1, 2, 3, 4, 5};
    my::SerialContainer<int> moved;

    // Act
    moved = std::move(original);

    // Assert
    ASSERT_EQ(moved.size(), 5);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);
    EXPECT_EQ(moved[3], 4);
    EXPECT_EQ(moved[4], 5);
    ASSERT_EQ(original.size(), 0);
}

TEST(SerialContainer, Insert) {
    // Arrange
    my::SerialContainer<int> container = {1, 2, 3, 4, 5};
    my::SerialContainer<int> to_insert = {99, 100};

    // Act
    container.insert(to_insert, 5);
    container.insert(to_insert, 2);
    container.insert(to_insert, 0);

    // Assert
    ASSERT_EQ(container.size(), 11);
    EXPECT_EQ(container[0], 99);
    EXPECT_EQ(container[1], 100);
    EXPECT_EQ(container[2], 1);
    EXPECT_EQ(container[3], 2);
    EXPECT_EQ(container[4], 99);
    EXPECT_EQ(container[5], 100);
    EXPECT_EQ(container[6], 3);
    EXPECT_EQ(container[7], 4);
    EXPECT_EQ(container[8], 5);
    EXPECT_EQ(container[9], 99);
    EXPECT_EQ(container[10], 100);
}

TEST(SerialContainer, Resize) {
    // Arrange
    my::SerialContainer<int> container = {1, 2, 3};
    int increased_size = 5;
    // Act & Assert: Increase size
    container.resize(5);
    ASSERT_EQ(container.size(), increased_size);
    ASSERT_EQ(container.capacity(), increased_size);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 3);
    EXPECT_EQ(container[3], 0);
    EXPECT_EQ(container[4], 0);

    // Act & Assert: Decrease size
    container.resize(2);
    ASSERT_EQ(container.size(), 2);
    ASSERT_EQ(container.capacity(), increased_size);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
}

TEST(SerialContainer, Empty) {
    // Arrange
    my::SerialContainer<int> container;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(container.size(), 0);
    ASSERT_TRUE(container.empty());
}


TEST(SerialContainer, PushBack) {
    // Arrange
    const size_t count = 20;
    my::SerialContainer<size_t> container;

    // Act
    for (size_t i = 0; i < count; ++i) {
        container.push_back(i);
    }

    // Assert
    ASSERT_EQ(container.size(), count);
    ASSERT_FALSE(container.empty());
    ASSERT_EQ(container.capacity(), count);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 1);
    EXPECT_EQ(container[2], 2);
    EXPECT_EQ(container[3], 3);
    EXPECT_EQ(container[4], 4);
    EXPECT_EQ(container[5], 5);
    EXPECT_EQ(container[6], 6);
    EXPECT_EQ(container[7], 7);
    EXPECT_EQ(container[8], 8);
    EXPECT_EQ(container[9], 9);
    EXPECT_EQ(container[10], 10);
    EXPECT_EQ(container[11], 11);
    EXPECT_EQ(container[12], 12);
    EXPECT_EQ(container[13], 13);
    EXPECT_EQ(container[14], 14);
    EXPECT_EQ(container[15], 15);
    EXPECT_EQ(container[16], 16);
    EXPECT_EQ(container[17], 17);
    EXPECT_EQ(container[18], 18);
    EXPECT_EQ(container[19], 19);

}

TEST(SerialContainer, Erase) {
    // Arrange
    const size_t count = 20;
    my::SerialContainer<size_t> container;

    // Act
    for (size_t i = 0; i < count; ++i) {
        container.push_back(i);
    }
    container.erase(3);

    // Assert
    ASSERT_EQ(container.size(), count-1);
    ASSERT_EQ(container[3], 4);
}

TEST(SerialContainer, IncreaseCapacity) {
    // Arrange
    const size_t capacity = 20;
    my::SerialContainer<size_t> container;

    // Act
    container.increase_capacity(capacity);

    // Assert
    ASSERT_EQ(container.capacity(), capacity);

    // Act 2
    container.increase_capacity(5);

    // Assert 2
    ASSERT_EQ(container.capacity(), capacity);

}

TEST(SerialContainer, Clear) {
// Arrange
my::SerialContainer<size_t> container;
for (size_t i = 0; i < 20; ++i) {
    container.push_back(i);
}

// Act
container.clear();

// Assert
ASSERT_EQ(container.size(), 0);
ASSERT_TRUE(container.empty());
}

class Test_Destructor {
    public:
        Test_Destructor() {
            ++count;
        }
        ~Test_Destructor() {
            --count;
        }
        static int get_count() { return count; }
    private:
        static int count;
};
int Test_Destructor::count = 0;
TEST(SerialContainer, Destructor) {
    {
        my::SerialContainer<Test_Destructor> container;
        for (size_t i = 0; i < 20; ++i) {
            container.push_back(Test_Destructor());
        }
        ASSERT_EQ(Test_Destructor::get_count(), 20);
    }
    ASSERT_EQ(Test_Destructor::get_count(), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}