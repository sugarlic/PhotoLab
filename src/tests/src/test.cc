#include <gtest/gtest.h>

#include "../../backend/includes/Model.h"

TEST(PLab_Test, test1) {
  EXPECT_ANY_THROW({
    s21::Model model;
    model.ReadImg("123");
  });
}

TEST(PLab_Test, test2) {
  EXPECT_NO_THROW({
    s21::Model model;
    model.ReadImg("/Users/sullustd/PhotoLab/Images/Lena.bmp");
  });
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}