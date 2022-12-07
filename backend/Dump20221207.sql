-- MySQL dump 10.13  Distrib 8.0.31, for Win64 (x86_64)
--
-- Host: localhost    Database: group4
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `accountId` int NOT NULL,
  `balance` double NOT NULL,
  `personId` int NOT NULL,
  `cardId` int NOT NULL,
  `creditLimit` double DEFAULT NULL,
  PRIMARY KEY (`accountId`),
  UNIQUE KEY `accountId_UNIQUE` (`accountId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `accountpermissions`
--

DROP TABLE IF EXISTS `accountpermissions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `accountpermissions` (
  `permissionId` int NOT NULL,
  `accountId` int NOT NULL,
  `personId` int NOT NULL,
  PRIMARY KEY (`permissionId`),
  UNIQUE KEY `idAccountPermissions_UNIQUE` (`permissionId`),
  KEY `Permission_account_idx` (`accountId`),
  KEY `Permission_person_idx` (`personId`),
  CONSTRAINT `AccountP_account` FOREIGN KEY (`accountId`) REFERENCES `account` (`accountId`),
  CONSTRAINT `AccountP_person` FOREIGN KEY (`personId`) REFERENCES `person` (`personId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `accountpermissions`
--

LOCK TABLES `accountpermissions` WRITE;
/*!40000 ALTER TABLE `accountpermissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `accountpermissions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `cardId` int NOT NULL,
  `pin` varchar(255) NOT NULL,
  `isCredit` tinyint DEFAULT NULL,
  `personId` int NOT NULL,
  `accountId` int DEFAULT NULL,
  PRIMARY KEY (`cardId`),
  UNIQUE KEY `cardId_UNIQUE` (`cardId`),
  UNIQUE KEY `personId_UNIQUE` (`personId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cardpermissions`
--

DROP TABLE IF EXISTS `cardpermissions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cardpermissions` (
  `permissionId` int NOT NULL,
  `cardId` int NOT NULL,
  `accountId` int NOT NULL,
  PRIMARY KEY (`permissionId`),
  KEY `CardP_Card_idx` (`cardId`),
  KEY `CardP_Account_idx` (`accountId`),
  CONSTRAINT `CardP_Account` FOREIGN KEY (`accountId`) REFERENCES `account` (`accountId`),
  CONSTRAINT `CardP_Card` FOREIGN KEY (`cardId`) REFERENCES `card` (`cardId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cardpermissions`
--

LOCK TABLES `cardpermissions` WRITE;
/*!40000 ALTER TABLE `cardpermissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `cardpermissions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `log`
--

DROP TABLE IF EXISTS `log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `log` (
  `logId` int NOT NULL,
  `date` datetime NOT NULL,
  `personId` int NOT NULL,
  `accountId` int NOT NULL,
  `cardId` int NOT NULL,
  `amount` double NOT NULL,
  PRIMARY KEY (`accountId`,`cardId`),
  UNIQUE KEY `logId_UNIQUE` (`logId`),
  KEY `log_card_idx` (`cardId`),
  CONSTRAINT `log_account` FOREIGN KEY (`accountId`) REFERENCES `account` (`accountId`),
  CONSTRAINT `log_card` FOREIGN KEY (`cardId`) REFERENCES `card` (`cardId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `log`
--

LOCK TABLES `log` WRITE;
/*!40000 ALTER TABLE `log` DISABLE KEYS */;
/*!40000 ALTER TABLE `log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person`
--

DROP TABLE IF EXISTS `person`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `person` (
  `personId` int NOT NULL,
  `firstname` varchar(255) DEFAULT NULL,
  `lastname` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`personId`),
  UNIQUE KEY `personId_UNIQUE` (`personId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `person`
--

LOCK TABLES `person` WRITE;
/*!40000 ALTER TABLE `person` DISABLE KEYS */;
/*!40000 ALTER TABLE `person` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-12-07 16:52:15
