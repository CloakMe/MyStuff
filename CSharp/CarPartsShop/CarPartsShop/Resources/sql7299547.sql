-- phpMyAdmin SQL Dump
-- version 4.7.1
-- https://www.phpmyadmin.net/
--
-- Host: sql7.freesqldatabase.com
-- Generation Time: Jul 30, 2019 at 10:20 AM
-- Server version: 5.5.58-0ubuntu0.14.04.1
-- PHP Version: 7.0.33-0ubuntu0.16.04.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `sql7299547`
--

-- --------------------------------------------------------

--
-- Table structure for table `CarParts`
--

CREATE TABLE `CarParts` (
  `id` int(11) NOT NULL,
  `name` varchar(50) NOT NULL DEFAULT '0',
  `carId` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `CarParts`
--

INSERT INTO `CarParts` (`id`, `name`, `carId`) VALUES
(1, 'breaks', 1),
(3, 'breaks', 3),
(4, 'FrontMirror', 7),
(5, 'FrontMirror', 8),
(6, 'FrontMirror', 9),
(7, 'FrontMirror', 10),
(8, 'hood', 1),
(9, 'hood', 3),
(10, 'hood', 4),
(11, 'hood', 5),
(12, 'hood', 6),
(13, 'hood', 7),
(14, 'hood', 8),
(15, 'hood', 15),
(16, 'hood', 16),
(17, 'seats', 11),
(18, 'seats', 12),
(19, 'seats', 13),
(20, 'seats', 14),
(21, 'RadioSet', 10),
(22, 'RadioSet', 9),
(46, 'breaksNissan', 6);

-- --------------------------------------------------------

--
-- Table structure for table `Cars`
--

CREATE TABLE `Cars` (
  `id` int(11) NOT NULL,
  `brand` varchar(50) NOT NULL DEFAULT '0',
  `model` varchar(50) NOT NULL DEFAULT '0',
  `year` int(10) UNSIGNED NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='Contains brand, model and production year';

--
-- Dumping data for table `Cars`
--

INSERT INTO `Cars` (`id`, `brand`, `model`, `year`) VALUES
(1, 'Ford', 'Focus', 2000),
(3, 'Ford', 'Focus', 1999),
(4, 'Ford', 'Focus', 2001),
(5, 'Ford', 'Fiesta', 2003),
(6, 'Nissan', 'Primera', 1998),
(7, 'Shevrolet', 'Prima', 2010),
(8, 'Shevrolet', 'Calos', 2010),
(9, 'Shevrolet', 'Cruze', 2019),
(10, 'Shevrolet', 'Malibu', 2019),
(11, 'Toyota', 'Corolla', 2012),
(12, 'Toyota', 'Corolla', 2013),
(13, 'Toyota', 'Corolla', 2014),
(14, 'Toyota', 'Corolla', 2015),
(15, 'Nissan', 'Primera', 1999),
(16, 'Nissan', 'Primera', 2000),
(17, 'Toyota', 'Yaris', 2010);

-- --------------------------------------------------------

--
-- Table structure for table `Shops`
--

CREATE TABLE `Shops` (
  `id` int(11) NOT NULL,
  `shopName` varchar(50) NOT NULL DEFAULT '0',
  `carPartId` int(11) DEFAULT NULL,
  `prise` double DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Shops`
--

INSERT INTO `Shops` (`id`, `shopName`, `carPartId`, `prise`) VALUES
(3, 'Slavejkov', 4, 46.79),
(4, 'Slavejkov', 5, 56),
(5, 'Slavejkov', 6, 70),
(6, 'Slavejkov', 7, 70),
(7, 'Slavejkov', 8, 80),
(8, 'Slavejkov', 9, 90),
(9, 'Slavejkov', 10, 100),
(10, 'Slavejkov', 11, 110),
(11, 'Slavejkov', 12, 120),
(12, 'Slavejkov', 13, 130),
(13, 'Slavejkov', 14, 140),
(14, 'Slavejkov', 15, 150),
(16, 'Slavejkov', 17, 170),
(17, 'Slavejkov', 18, 180),
(18, 'Slavejkov', 19, 190),
(19, 'Slavejkov', 20, 200),
(20, 'Slavejkov', 21, 210),
(21, 'Slavejkov', 22, 22),
(22, 'Mladost', 3, 50.1),
(23, 'Mladost', 4, 50.1),
(24, 'Mladost', 5, 57),
(25, 'Mladost', 6, 60),
(26, 'Mladost', 7, 74),
(27, 'Mladost', 8, 84),
(28, 'Mladost', 9, 94),
(29, 'Mladost', 10, 94),
(30, 'Mladost', 11, 94),
(31, 'Mladost', 12, 94),
(32, 'Mladost', 13, 94),
(33, 'Mladost', 14, 124),
(34, 'Mladost', 15, 124),
(35, 'Mladost', 16, 167),
(36, 'Mladost', 17, 167),
(37, 'Mladost', 18, 167),
(38, 'Mladost', 19, 167),
(39, 'Mladost', 20, 167),
(40, 'Mladost', 21, 177),
(41, 'Mladost', 22, 200);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `CarParts`
--
ALTER TABLE `CarParts`
  ADD KEY `Column 1` (`id`),
  ADD KEY `PartToCar` (`carId`);

--
-- Indexes for table `Cars`
--
ALTER TABLE `Cars`
  ADD KEY `Column 1` (`id`);

--
-- Indexes for table `Shops`
--
ALTER TABLE `Shops`
  ADD KEY `Column 1` (`id`),
  ADD KEY `CarPartToShop` (`carPartId`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `CarParts`
--
ALTER TABLE `CarParts`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=47;
--
-- AUTO_INCREMENT for table `Cars`
--
ALTER TABLE `Cars`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;
--
-- AUTO_INCREMENT for table `Shops`
--
ALTER TABLE `Shops`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=44;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `CarParts`
--
ALTER TABLE `CarParts`
  ADD CONSTRAINT `PartToCar` FOREIGN KEY (`CarID`) REFERENCES `Cars` (`id`);

--
-- Constraints for table `Shops`
--
ALTER TABLE `Shops`
  ADD CONSTRAINT `CarPartToShop` FOREIGN KEY (`carPartID`) REFERENCES `CarParts` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
