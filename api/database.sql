/*
 Navicat Premium Data Transfer

 Source Server         : dealership
 Source Server Type    : MySQL
 Source Server Version : 80200 (8.2.0)
 Source Host           : localhost:3306
 Source Schema         : ATM

 Target Server Type    : MySQL
 Target Server Version : 80200 (8.2.0)
 File Encoding         : 65001

 Date: 24/04/2024 15:45:39
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for Account
-- ----------------------------
DROP TABLE IF EXISTS `Account`;
CREATE TABLE `Account`  (
  `IBAN` varchar(18) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `FirstName` varchar(40) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `LastName` varchar(40) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Email` varchar(45) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `BirthDate` date NULL DEFAULT NULL,
  `Balance` int NULL DEFAULT NULL,
  PRIMARY KEY (`IBAN`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of Account
-- ----------------------------

-- ----------------------------
-- Table structure for Cards
-- ----------------------------
DROP TABLE IF EXISTS `Cards`;
CREATE TABLE `Cards`  (
  `CardID` int NOT NULL,
  `CardNR` int NULL DEFAULT NULL,
  `ExpDate` date NULL DEFAULT NULL,
  `Blocked` int NULL DEFAULT NULL,
  `Account_IBAN` varchar(18) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`CardID`) USING BTREE,
  INDEX `Account_IBAN`(`Account_IBAN` ASC) USING BTREE,
  CONSTRAINT `Cards_ibfk_1` FOREIGN KEY (`Account_IBAN`) REFERENCES `Account` (`IBAN`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of Cards
-- ----------------------------

-- ----------------------------
-- Table structure for Pincodes
-- ----------------------------
DROP TABLE IF EXISTS `Pincodes`;
CREATE TABLE `Pincodes`  (
  `PinID` int NOT NULL,
  `PinCode` int NULL DEFAULT NULL,
  `CardID` int NULL DEFAULT NULL,
  PRIMARY KEY (`PinID`) USING BTREE,
  INDEX `CardID`(`CardID` ASC) USING BTREE,
  CONSTRAINT `Pincodes_ibfk_1` FOREIGN KEY (`CardID`) REFERENCES `Cards` (`CardID`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of Pincodes
-- ----------------------------

-- ----------------------------
-- Table structure for Transactions
-- ----------------------------
DROP TABLE IF EXISTS `Transactions`;
CREATE TABLE `Transactions`  (
  `ID` int NOT NULL,
  `Date` date NULL DEFAULT NULL,
  `Amount` int NULL DEFAULT NULL,
  `Account_IBAN` varchar(18) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE,
  INDEX `Account_IBAN`(`Account_IBAN` ASC) USING BTREE,
  CONSTRAINT `Transactions_ibfk_1` FOREIGN KEY (`Account_IBAN`) REFERENCES `Account` (`IBAN`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of Transactions
-- ----------------------------

SET FOREIGN_KEY_CHECKS = 1;
