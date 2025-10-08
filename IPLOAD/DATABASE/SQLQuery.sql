--BUILT IN

-- F1 for finding maimum value
select max (Total_Ammount) from Orders;
-- F2 for finding average 
select avg (Total_Ammount) from Orders;
-- F3 for finding minimum price
select min (Total_Ammount) from Orders;
-- F4 for finding number of enteries
select count (Total_Ammount) from Orders;
-- F5 for summation
select sum (Total_Ammount) from Orders;

--USER DEFINED

-- F6 to add a new customer
CREATE FUNCTION AddCustomer(@FirstName VARCHAR(50), @LastName VARCHAR(50), @PhoneNumber VARCHAR(15))
RETURNS INT
AS
BEGIN
    DECLARE @CustomerID INT;
    INSERT INTO Customers (FirstName, LastName, PhoneNumber)
    VALUES (@FirstName, @LastName, @PhoneNumber);
    SET @CustomerID = SCOPE_IDENTITY();
    RETURN @CustomerID;
END;

-- F7 to place a new order
CREATE FUNCTION PlaceOrder(@CustomerID INT, @TotalAmount DECIMAL(10, 2), @StatusID INT, @StaffID INT)
RETURNS INT
AS
BEGIN
    DECLARE @OrderID INT;
    INSERT INTO Orders (CustomerID, TotalAmount, StatusID, StaffID)
    VALUES (@CustomerID, @TotalAmount, @StatusID, @StaffID);
    SET @OrderID = SCOPE_IDENTITY();
    RETURN @OrderID;
END;

-- F8 to update inventory when an order is placed
CREATE FUNCTION UpdateInventory(@MenuItemID INT, @Quantity INT)
RETURNS VOID
AS
BEGIN
    UPDATE Inventory
    SET Quantity = Quantity - @Quantity
    WHERE MenuItemID = @MenuItemID;
END;

-- UDF to make a reservation
CREATE FUNCTION MakeReservation(@CustomerID INT, @ReservationDate TIMESTAMP, @NumOfGuests INT, @TableNumber INT)
RETURNS INT
AS
BEGIN
    DECLARE @ReservationID INT;
    INSERT INTO Reservations (CustomerID, ReservationDate, NumOfGuests, TableNumber)
    VALUES (@CustomerID, @ReservationDate, @NumOfGuests, @TableNumber);
    SET @ReservationID = SCOPE_IDENTITY();
    RETURN @ReservationID;
END;

-- F9 to cancel a reservation
CREATE FUNCTION CancelReservation(@ReservationID INT)
RETURNS VOID
AS
BEGIN
    DELETE FROM Reservations
    WHERE ReservationID = @ReservationID;
END;

-- F10 to update order status
CREATE FUNCTION UpdateOrderStatus(@OrderID INT, @StatusID INT)
RETURNS VOID
AS
BEGIN
    UPDATE Orders
    SET StatusID = @StatusID
    WHERE OrderID = @OrderID;
END;

-- F11 to get available tables
CREATE FUNCTION GetAvailableTables(@ReservationDate TIMESTAMP)
RETURNS TABLE
AS
RETURN
    SELECT TableNumber
    FROM Tables
    WHERE TableNumber NOT IN (
        SELECT TableNumber
        FROM Reservations
        WHERE ReservationDate = @ReservationDate
    );

-- F12 to get order details
CREATE FUNCTION GetOrderDetails(@OrderID INT)
RETURNS TABLE
AS
RETURN
    SELECT od.OrderDetailID, m.Name AS MenuItem, od.Quantity, od.Price
    FROM OrderDetails od
    INNER JOIN MenuItems m ON od.MenuItemID = m.Menu_ID
    WHERE od.OrderID = @OrderID;

-- F13 to get total sales
CREATE FUNCTION GetTotalSales(@StartDate TIMESTAMP, @EndDate TIMESTAMP)
RETURNS DECIMAL(10, 2)
AS
BEGIN
    DECLARE @TotalSales DECIMAL(10, 2);
    SELECT @TotalSales = SUM(TotalAmount)
    FROM Orders
    WHERE OrderDateTime BETWEEN @StartDate AND @EndDate;
    RETURN @TotalSales;
END;

-- 
F14 to get employee sales
CREATE FUNCTION GetEmployeeSales(@StaffID INT, @StartDate TIMESTAMP, @EndDate TIMESTAMP)
RETURNS DECIMAL(10, 2)
AS
BEGIN
    DECLARE @EmployeeSales DECIMAL(10, 2);
    SELECT @EmployeeSales = SUM(TotalAmount)
    FROM Orders
    WHERE StaffID = @StaffID AND OrderDateTime BETWEEN @StartDate AND @EndDate;
    RETURN @EmployeeSales;
END;

 