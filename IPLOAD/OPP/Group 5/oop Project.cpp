#include<iostream>  // to compile the code 
#include<string>    //manuplating ,working with string
#include<iomanip>   //to set the width of output result in console
#include<fstream>  // to work with file
#include<windows.h>
#include<ctime>
using namespace std;
// Function to get the current date and time as a string
string getCurrentDateTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now));
    return buf;
}


// global variables
const int MAX_MENU_ITEMS = 100;    //limiting items
const int MAX_ORDER_ITEMS = 100;  //limiting orders
const int MAX_TABLES = 20;        // limiting tables   
const int MAX_WAITERS = 10;      //limited waiters
const int MAX_TAKEAWAYS = 50;    // Limited Takeaway

// for colouring
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


// Basic colors
void black_color() { setColor(0); }
void blue_color() { setColor(1); }
void green_color() { setColor(2); }
void aqua_color() { setColor(3); }
void red_color() { setColor(4); }
void purple_color() { setColor(5); }
void yellow_color() { setColor(6); }
void white_color() { setColor(7); }
void gray_color() { setColor(8); }
void light_blue_color() { setColor(9); }
void light_green_color() { setColor(10); }
void light_aqua_color() { setColor(11); }
void light_red_color() { setColor(12); }
void light_purple_color() { setColor(13); }
void light_yellow_color() { setColor(14); }
void bright_white_color() { setColor(15); }
void sian_color() {setColor(16);}


// Text with background colors (foreground + background)
void blue_bg_white_text() { setColor(1 + 7 * 16); }
void green_bg_white_text() { setColor(2 + 7 * 16); }
void red_bg_white_text() { setColor(4 + 7 * 16); }
void yellow_bg_black_text() { setColor(6 + 0 * 16); }
void white_bg_black_text() { setColor(7 + 0 * 16); }
void black_bg_white_text() { setColor(0 + 15 * 16); }

// Custom combinations
void custom_color_1() { setColor(5 + 10 * 16); }  // Purple text on light green background
void custom_color_2() { setColor(3 + 12 * 16); }  // Aqua text on light red background
void custom_color_3() { setColor(14 + 1 * 16); }  // Yellow text on blue background

class MenuItem {
	
    private:
    	
        string name;
        string description;
        double price;

    public:
    	
        MenuItem(string n, string desc, double p) : name(n), description(desc), price(p) {} //parametrized constructor  
        MenuItem() : name(""), description(""), price(0.0) {}        // default constructor

    void display() const {           //to display right way by width fuction
    	                                     
        cout<<setw(20)<<left<<name<<setw(30)<<left<<description<<setw(10)<<left<<price<<endl;
    }

    double getPrice() const {                    //getter fuction
    	
        return price;
    }

    string getName() const {                   //getter fuction
    	
        return name;
    }

    string getDescription() const {          //getter fuction
    	
        return description;
    }
};

class Menu {
	
    private:
    	
        MenuItem items[MAX_MENU_ITEMS];
        int itemCount;

    public:
    	
    Menu() : itemCount(0) {}     // Default constructor

    void addItem(const MenuItem& item) {        // Item storing fuction with limit upto 100
    	
        if (itemCount < MAX_MENU_ITEMS) {      //Condition
        	
            items[itemCount++] = item;
            
        } 
        
		else {
			// cerr is mostly used 
            cerr<<"Menu is full. Cannot add more items."<<endl;
            
        }
    }
//By marking display() function  as const,we will not modify any member variables of the class.

    void display() const {          // To set the hardcode according to the design
    
        cout<<setw(20)<<left<<"Name"<<setw(30)<<left<<"Description"<<setw(10)<<left<<"Price"<<endl;
        cout<<setfill('-')<<setw(60)<<"-"<<setfill(' ')<<endl;
        
        for (int i = 0; i < itemCount; ++i) {   // Loop has been set to display items and menu 
        
            items[i].display();
            
        }
    }
//By marking display() function  as const,we will not modify any member variables of the class.
    MenuItem getItem(int index) const { // retrieve a menu item from the array of menu items.
    
        if (index >= 1 && index <= itemCount) {
       	
            return items[index - 1];
            
        } 
		else {
			
            cout<<"Invalid menu item index"<<endl;
            return MenuItem();
        }
    }
// it search  through the menu items and save  their name, description, and price to the file.
    void saveToFile(const string& filename) const {
    	
        ofstream file(filename.c_str());
        
        if (file.is_open()) {
        	
            for (int i = 0; i < itemCount; ++i) {
            	// calling getters 
                file<<items[i].getName()<<"\n"<<items[i].getDescription()<<"\n"<< items[i].getPrice()<<"\n";
                
            }
            
            file.close();
            
        } 
		else {
			
// the file cannot be opened,  prints an error message to cerr.
			
            cerr<<"Unable to open file for writing."<<endl;
            
        }
    }
//The purpose of this function is to load menu items from a file 
    void loadFromFile(const string& filename) {
    	
        ifstream file(filename.c_str());
        
        if (file.is_open()) {
        	
            itemCount = 0;
            string name, description;
            double price;
            
            while (getline(file, name) && getline(file, description) && file >> price) {
            	
                file.ignore(); // to ignore the newline character after reading the price
                addItem(MenuItem(name, description, price));
            }
            file.close();
        } 
		else {
// if the file doesnot exist then print cerr			
            cerr<<"Unable to open file for reading."<<endl;
        }
    }
};

class Order {
	
    private:
    	// another class within the class  NESTED CLASS
    class OrderItem {
    	
         public:
         	
        MenuItem item;
        int quantity;

        OrderItem(const MenuItem& itm, int qty) : item(itm), quantity(qty) {} //parameterized constructor
        OrderItem() : item(), quantity(0) {} // default constructor
    };

    OrderItem orderItems[MAX_ORDER_ITEMS];  // using global variable
    
    int orderCount;

public:
	
    Order() : orderCount(0) {}  //default constructor

    void addItem(const MenuItem& item, int quantity) {  // using the reference class menuitem and obj item 
    	
        if (orderCount < MAX_ORDER_ITEMS) {
        	
            orderItems[orderCount++] = OrderItem(item, quantity);  // limit checking for oder count
        } 
		else {
			// if there is no space then 
            cerr<<"Order is full. Cannot add more items."<<endl;
        }
    }

    void display() const {
    	// using iomanip built in fuction to set the display
    	
        cout<<setw(20)<<left<<"Name"<<setw(10)<<left<<"Price"<<setw(10)<<left<<"Quantity"<<setw(10)<<left<<"Total"<<endl;
        cout<<setfill('-')<<setw(50)<<"-"<<setfill(' ')<<endl;

        for (int i = 0; i < orderCount; ++i) {
        	
            cout<<setw(20)<<left<<orderItems[i].item.getName()<<setw(10)<<left<<orderItems[i].item.getPrice()<<setw(10)<<left<<orderItems[i].quantity<<setw(10)<<left<<orderItems[i].item.getPrice()*orderItems[i].quantity<<endl;
        }
    }

    double getTotalBill(double taxRate = 0.0, double discount = 0.0) const {  // fuction used for billing and discount
        double total = 0;
        
        for (int i = 0; i < orderCount; ++i) {
        	// array used to multiply the price and quantity
            total += orderItems[i].item.getPrice() * orderItems[i].quantity;
        }
        total += total * taxRate;
        total -= discount;
        return total;
    }
};


class Table {
	
    private:
    	
       int tableNumber;
       bool occupied;
       bool reserved;
       Order order;

    public:
    	
    Table() : tableNumber(0), occupied(false), reserved(false) {}   // default constructor
    
    Table(int number) : tableNumber(number), occupied(false), reserved(false) {}   //parameterized constructor

    int getTableNumber() const {
    	
        return tableNumber;      //getter fuction
        
    }

    bool isOccupied() const {
    	
        return occupied;          //getter fuction
        
    }

    bool isReserved() const {
    	
        return reserved;            //getter fuction
        
    }

    Order& getOrder() {
    	 
        return order;              //getter fuction
        
    }

    void occupy() {    // if table is occupied
    	
        occupied = true;         
        
    }

    void vacate() {    // if table is free
    	
        occupied = false;
        reserved = false;
        order = Order(); 
        
    }

    void reserve() {    // if table is reserved
    	
        reserved = true;
        
    }

    void displayOrder() const {          // fuction for displaying order
    	
        cout<<"Table "<<tableNumber<<" Order Summary:"<<endl;
    
        order.display();
        
    }

    double getBill(double taxRate = 0.0, double discount = 0.0) const {   // printing bill
    	
        return order.getTotalBill(taxRate, discount);
        
    }
};

class TakeawayOrder {
private:
    int orderNumber;
    Order order;

public:
    TakeawayOrder() : orderNumber(0) {}
    TakeawayOrder(int number) : orderNumber(number) {}

    int getOrderNumber() const {
        return orderNumber;
    }

    Order& getOrder() {
        return order;
    }

    void displayOrder() const {
        cout << "Takeaway Order " << orderNumber << " Summary:" << endl;
        order.display();
    }

    double getBill(double taxRate = 0.0, double discount = 0.0) const {
        return order.getTotalBill(taxRate, discount);
    }
};
class User {
	 
    protected:
       string username;
       string password;

public:
	
    User(string uname, string pass) : username(uname), password(pass) {}    // parameterized constructor


    string getUsername() const {
    	
        return username;
        
    }
   // verifying the name and password
    bool authenticate(const string& uname, const string& pass) const {
    	
        return username == uname && password == pass;
        
    }
// overiding implementation of on their  own
    virtual void menuActions(Menu& menu, Table tables[], int& tableCount,TakeawayOrder takeaways[], int& takeawayCount) = 0; 
};

class Admin : public User {       // child of user
	
    public:
    	
    Admin(string uname, string pass) : User(uname, pass) {}  //parameterized constructor 

/* This function overrides the menuActions function declared in the base class User
 this fuction is used to add items to the menu by the admin */
 
    void menuActions(Menu& menu, Table tables[], int& tableCount,TakeawayOrder takeaways[], int& takeawayCount) override {
    	
        int choice;
        
        //loop for repeatation until condition is fullfilled
        
        do {
        	cout<<endl;
        	white_bg_black_text();
            cout<<"\nAdmin Menu:"<<endl<<endl;
            light_aqua_color();
        cout<<"\t******************************"<<endl;
        cout<<"\t|                            |"<<endl;
        cout<<"\t* 1. Add Menu Item           *"<<endl;
        cout<<"\t|                            |"<<endl;
        cout<<"\t* 2. Display Menu            *"<<endl;
        cout<<"\t|                            |"<<endl;
		cout<<"\t* 3. Save Menu to File       *"<<endl;
		cout<<"\t|                            |"<<endl;
        cout<<"\t* 4. Load Menu from File     *"<<endl;
        cout<<"\t|                            |"<<endl;
        cout<<"\t* 5. View Tables             *"<<endl;
        cout<<"\t|                            |"<<endl;
        cout<<"\t* 6. View Total Earnings     *"<<endl;
        cout<<"\t|                            |"<<endl;
        cout<<"\t* 7. View Takeaway Orders    *"<<endl;
        cout<<"\t|                            |"<<endl;
        cout<<"\t* 8. Exit Admin Menu         *"<<endl;
        cout<<"\t|                            |"<<endl;
        cout<<"\t******************************"<<endl<<endl; 
		bright_white_color();   
            cout<<"Enter your choice: ";
            cin>>choice;
            
        // To select given options
            switch (choice) {
        // using fuctions of menu class   	
                case 1: {
                	
                    string name, description;
                    double price;
                    cout<<endl;
                    white_bg_black_text();
                    cout<<"Enter Food name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout<<"Enter Food description: ";
                    getline(cin, description);
                    cout<<"Enter Food price: ";
                    cin>>price;
                    menu.addItem(MenuItem(name, description, price));
                    break;
                    
                }
                case 2:
                	cout<<endl;
                	green_color();
                    menu.display();
                    break;
                    
                case 3: {
                	cout<<endl;
                    string filename;
                    white_bg_black_text();
                    cout<<"Enter filename to save menu: ";
                    cin>>filename;
                    menu.saveToFile(filename);
                    break;
                    
                }
                case 4: {
                	cout<<endl;
                    string filename;
                    cout<<"Enter filename to load menu: ";
                    cin>>filename;
                    menu.loadFromFile(filename);
                    break;
                    
                }
                case 5: {
                	cout<<endl;
                    cout<<"Tables:\n";
                    for (int i = 0; i < tableCount; ++i) {
                        cout<<"Table "<<tables[i].getTableNumber()<<": "<<(tables[i].isOccupied() ? "Occupied" : "Vacant")<<(tables[i].isReserved() ? " (Reserved)" : "")<<endl;
                    }
                    break;
                }
                
                case 6: {
                	
                	cout<<endl;
                	 double totalEarnings = 0;
                    for (int i = 0; i < tableCount; ++i) {
                        totalEarnings += tables[i].getBill();
                    }
                    for (int i = 0; i < takeawayCount; ++i) {
                        totalEarnings += takeaways[i].getBill();
                    }
                    cout << "Total earnings: $" << totalEarnings << endl;
                    cout << "\t\t\t\t\t\t\t\t\t\t\t " << getCurrentDateTime() << endl;
                    break;
                }
                case 7: {
                	cout<<endl;
                    cout << "Takeaway Orders:\n";
                    for (int i = 0; i < takeawayCount; ++i) {
                        takeaways[i].displayOrder();
                        cout << "Total: $" << takeaways[i].getBill() << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t " << getCurrentDateTime() << endl;
                    }
                    break;
                }
                
                case 8:
                	cout<<endl;
                    cout<<"Exiting Admin Menu\n";
                    break;
                    
                default:
                	
                    cerr<<"Invalid choice. Try again.\n";
            }
        } 
    while (choice != 8);

    }
};

class Waiter : public User {
	
public:
	
    Waiter(string uname, string pass) : User(uname, pass) {}   // parameterized constructor
    
//This function overrides the menuActions function declared in the base class User

    void menuActions(Menu& menu, Table tables[], int& tableCount,TakeawayOrder takeaways[], int& takeawayCount) override {
    	
        int choice;
        
        do {
        	cout<<endl;
        	white_bg_black_text();
            cout<<"\nWaiter Menu:"<<endl<<endl;
            green_color();
        cout<<" ________________________________"<<endl;
        cout<<" |                              |"<<endl;            
        cout<<" * 1. View Tables               *"<<endl;
        cout<<" |                              |"<<endl; 
        cout<<" * 2. Take Order                *"<<endl;
        cout<<" |                              |"<<endl; 
        cout<<" * 3. Print Bill                *"<<endl;
        cout<<" |                              |"<<endl; 
        cout<<" * 4.View Takeaway Order        *"<<endl;
        cout<<" |                              |"<<endl; 
        cout<<" * 5.Generate Bill for Takeaway *"<<endl;
        cout<<" |                              |"<<endl; 
        cout<<" * 6.Exit Waiter Menu           *"<<endl;
        cout<<" |______________________________|"<<endl<<endl
		;    
		bright_white_color();
            cout<<"Enter your choice: ";
            cin>>choice;

            switch (choice) {
            	
                case 1: {
                	cout<<endl;
                    cout<<"Tables:\n";
                    for (int i = 0; i < tableCount; ++i) {
                        cout<<"Table "<<tables[i].getTableNumber()<<": "<<(tables[i].isOccupied() ? "Occupied" : "Vacant")<<(tables[i].isReserved() ? " (Reserved)" : "") << endl;
                    }
                    break;
                }
                
                case 2: {
                    int tableNumber;
                    cout<<endl;
                    cout<<"Enter table number to take order (1-" << MAX_TABLES << "): ";
                    cin>>tableNumber;
                    
                    if (tableNumber < 1 || tableNumber > MAX_TABLES) {
                        cout<<"Invalid table number. Exiting."<<endl;
                        return;
                    }
                    
                    Table& table = tables[tableNumber - 1];
                    
                    if (!table.isOccupied()) {
                        cout<<"Table "<<tableNumber<<" is not occupied."<<endl;
                        return;
                    }

                    int itemNumber, quantity;
                    
                    cout<<"Here is the menu:\n";
                    menu.display(); 
                    cout<<"Enter the item number you'd like to order (0 to finish): ";
                    cout << "\t\t\t\t\t\t\t\t\t\t\t " << getCurrentDateTime() << endl;
                    
                    while (cin>>itemNumber && itemNumber != 0) {
                    	
                        cout<<"Enter quantity: ";
                        cin>>quantity;
                        MenuItem item = menu.getItem(itemNumber);
                        
                        if (item.getName() != "") {
                            table.getOrder().addItem(item, quantity);
                            cout<<"Added "<<quantity<<"x "<<item.getName()<<" to the order."<<endl;
                        } else {
                            cout<<"Invalid item number. Please try again."<<endl;
                        }
                        cout<<"Enter the item number you'd like to order (0 to finish): ";
                    }
                    cout<<"Order taken successfully for Table "<<tableNumber<<"."<<endl;
                    break;
                }
                
                case 3: {
                    int tableNumber;
                    cout<<endl;
                    cout<<"Enter table number to print bill (1-"<< MAX_TABLES <<"): ";
                    cin>>tableNumber;
                   
                    
                    if (tableNumber < 1 || tableNumber > MAX_TABLES) {
                        cout<<"Invalid table number. Exiting."<<endl;
                        return;
                    }
                    
                    Table& table = tables[tableNumber - 1];
                    
                    if (!table.isOccupied()) {
                        cout<<"Table "<<tableNumber<<" is not occupied."<<endl;
                        return;
                    }
					// for billing and time printing
                    table.displayOrder();
                    double bill = table.getBill(0.10); 
                    cout<<"Total Bill (including tax): $"<<bill<<endl;
                    cout << "\t\t\t\t\t\t\t\t\t\t\t " << getCurrentDateTime() << endl;
                    break;
                }
                case 4: {
                    int orderNumber;
                    cout<<endl;
                    cout << "Enter takeaway order number: ";
                    cin >> orderNumber;

                    TakeawayOrder* takeaway = nullptr;
                    for (int i = 0; i < takeawayCount; ++i) {
                        if (takeaways[i].getOrderNumber() == orderNumber) {
                            takeaway = &takeaways[i];
                            break;
                        }
                    }

                    if (takeaway) {
                        takeaway->displayOrder();
                    } else {
                        cout << "Takeaway order not found.\n";
                    }
                    break;
                }
                case 5: {
                    int orderNumber;
                    cout<<endl;
                    cout << "Enter takeaway order number: ";
                    cin >> orderNumber;

                    TakeawayOrder* takeaway = nullptr;
                    for (int i = 0; i < takeawayCount; ++i) {
                        if (takeaways[i].getOrderNumber() == orderNumber) {
                            takeaway = &takeaways[i];
                            break;
                        }
                    }

                 
                    takeaway->displayOrder();
                    double bill = takeaway->getBill(0.10); 
                    cout<<"Total Bill (including tax): $"<<bill<<endl;
                    cout << "\t\t\t\t\t\t\t\t\t\t\t " << getCurrentDateTime() << endl;
                    break;
                }
            
                case 6:
                    cout<<"Exiting Waiter Menu\n";
                    break;
                    
                default:
                    cout<<"Invalid choice. Try again.\n";
            }
            
        }
		 while (choice != 6);
    }
};

class Customer : public User {
	
public:
	
    Customer(string uname, string pass) : User(uname, pass) {}  //parameterized fuction 
//This function overrides the menuActions function declared in the base class User
    void menuActions(Menu& menu, Table tables[], int& tableCount,TakeawayOrder takeaways[], int& takeawayCount) override {
    	
        int choice;
        cout<<endl;
        white_bg_black_text();
        cout<<"Welcome! Please choose an option:"<<endl<<endl;
        light_red_color();
        cout<<" _________________________"<<endl;
        cout<<" |                       |"<<endl;
        cout<<" * 1.Reserve a table     *"<<endl;
        cout<<" |                       |"<<endl;
		cout<<" * 2.Dine in             *"<<endl;
		cout<<" |                       |"<<endl;
        cout<<" * 3.Takeaway Order      *"<<endl;
        cout<<" |_______________________|"<<endl<<endl;
        bright_white_color();
        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice) {
        	
            case 1: {
            	
                int tableNumber;
            	cout<<endl;
                cout<<"Enter table number to reserve (1-"<< MAX_TABLES <<"): ";
                cin>>tableNumber;
                
                if (tableNumber < 1 || tableNumber > MAX_TABLES) {
                    cout<<"Invalid table number. Exiting."<<endl;
                    return;
                }
                
                Table& table = tables[tableNumber - 1];
                
                if (table.isReserved() || table.isOccupied()) {
                    cout<<"Sorry, the table is not available for reservation. Please choose another table or dine in."<<endl;
                    return;
                }
                table.reserve();
                
                cout<<"Table "<<tableNumber<<" reserved successfully!"<<endl;
                break;
            }
            
            case 2: {
                int tableNumber;
            	cout<<endl;
                cout<<"Enter table number to dine in (1-"<< MAX_TABLES<< "): ";
                cin>>tableNumber;
                
                if (tableNumber < 1 || tableNumber > MAX_TABLES) {
                    cout<<"Invalid table number. Exiting."<<endl;
                    return;
                }
                
                Table& table = tables[tableNumber - 1];
                
                if (table.isOccupied()) {
                    cout<<"Sorry, the table is already occupied. Please choose another table."<<endl;
                    return;
                }
                
                table = Table(tableNumber); 
                table.occupy();
                cout<<"You are now seated at Table "<<tableNumber<<"."<<endl;

                cout<<"Please call a waiter to take your order."<<endl;
                
                break;
            }
            case 3: {
                 int orderNumber;
                    cout<<endl;
                    cout << "Enter takeaway order number: ";
                    cin >> orderNumber;

                    TakeawayOrder* takeaway = nullptr;
                    for (int i = 0; i < takeawayCount; ++i) {
                        if (takeaways[i].getOrderNumber() == orderNumber) {
                            takeaway = &takeaways[i];
                            break;
                        }
                    }

                    if (!takeaway) {
                        if (takeawayCount < MAX_TAKEAWAYS) {
                            takeaways[takeawayCount++] = TakeawayOrder(orderNumber);
                            takeaway = &takeaways[takeawayCount - 1];
                        } else {
                            cout << "Cannot take more takeaway orders.\n";
                            break;
                        }
                    }

                    int itemNumber, quantity;
                    do {
                        menu.display();
                        cout << "Enter menu item number to add to order (0 to finish): ";
                        cin >> itemNumber;
                        if (itemNumber != 0) {
                            cout << "Enter quantity: ";
                            cin >> quantity;
                            takeaway->getOrder().addItem(menu.getItem(itemNumber), quantity);
                        }
                    } while (itemNumber != 0);
                     cout<<"To Generate Bill Go To Waiter login"<<endl;
                    break;
            }  
			
			
			          
            default:
                cout<<"Invalid choice. Exiting."<< endl;
        }
    }
};

int main() {
    
	light_aqua_color();
	// Designing
	cout<<" \t\t\t\t\t_________________________________________"<<endl;
	cout<<" \t\t\t\t\t|                                       | "<<endl;
    cout<<" \t\t\t\t\t|*   RESTAURENT MANAGEMENT SYSTEM      *|"<<endl;
   	cout<<" \t\t\t\t\t|*                                     *| "<<endl;
    cout<<" \t\t\t\t\t|*        MAD   RESTAURENT             *| "<<endl;
    cout<<" \t\t\t\t\t|_______________________________________|"<<endl<<endl;
    
    cout << "<---------------------->Welcome a Place Where People Fall  in Love with Food<----------------------------->" << endl;
    //cout<<"Welcome a Place Where People Fall  in Love with Food"<<endl;
// creating obj pf menu
    Menu menu;
    TakeawayOrder takeaways[MAX_TAKEAWAYS];
    int takeawayCount = 0;
 // deafult menu entering 
    cout<<endl;
   // menu.addItem(MenuItem("ME));
   
    menu.addItem(MenuItem("1.Burger               ","Classic beef burger             ", 8.99));
    menu.addItem(MenuItem("2.Mad special Burger   ","grilled burger with chese       ", 7.00));
    menu.addItem(MenuItem("3.Black star Burger    ","two beef patties                ", 10.00));
    menu.addItem(MenuItem("4.Morocian Burger      ","with morocian sauce             ", 11.00));
    menu.addItem(MenuItem("5.Mexican Pizza        ","Margherita sauce                ", 12.99));
    menu.addItem(MenuItem("6.Fajita Pizza         ","chilly sauce                    ", 11.99));
    menu.addItem(MenuItem("7.Fiery Pizza          ","MAD special sauce               ", 13.99));
    menu.addItem(MenuItem("8.crown crust Pizza    ","stuffed with kababs             ", 12.99));
    menu.addItem(MenuItem("9.Alferodo pasta       ","with white sauce                ", 9.99));
    menu.addItem(MenuItem("10.Mac-n-Cheese pasta  ","Loaded with Cheese              ", 7.99));
    menu.addItem(MenuItem("11.Spinach pasta       ","with  fresh spinach sauce       ", 8.99));
    menu.addItem(MenuItem("12.French Fries        ","with special sauce              ",3.99));
    menu.addItem(MenuItem("13.Loaded Fries        ","with cheese and chunks          ",3.99));
    menu.addItem(MenuItem("14.lemonade            ","made with fresh lemon           ",1.00));
    menu.addItem(MenuItem("15.Pink lady           ","made with Strawberry            ",5.00));
    menu.addItem(MenuItem("15.Mojito              ","Soda with ice and flavor        ",3.00));
    
    Table tables[MAX_TABLES];   // using global variable to limit tables
    // using array for max table 
    
    for (int i = 0; i < MAX_TABLES; ++i) {
    	
        tables[i] = Table(i + 1); 
        
    }
    
    int tableCount = MAX_TABLES;  // using global variable to limit tables

    bool exitProgram = false;    
 
 // repeating loop to start programme
 
    do {
    
        int userType;
         bright_white_color();      
		cout<<"  Enter numeric values for "<<endl<<endl;
		 aqua_color();
        cout<<" ******************************"<<endl;
        cout<<" |                            |"<<endl;
		cout<<" *  1) Admin                  *"<<endl;
        cout<<" |                            |"<<endl;
		cout<<" *  2) Waiter                 *"<<endl;
        cout<<" |                            |"<<endl;
		cout<<" *  3) Customer               *"<<endl;
        cout<<" ******************************"<<endl<<endl;
        bright_white_color();
        cout<<"  Your choice :";
        cin>>userType;


        User* user = NULL;
        
        if (userType == 1) {
        	
            user = new Admin("admin", "password");
            string username, password;
            cout<<"Enter admin username: ";
            cin>>username;
            cout<<"Enter admin password: ";
            cin>>password;

            if (user->authenticate(username, password)) {
                user->menuActions(menu, tables, tableCount,takeaways, takeawayCount);
            } 
			else {
                cout<<"Authentication failed. Exiting."<<endl;
                
                delete user;
                return 1;
            }
        }
	    else if (userType == 2) {
	    	
            user = new Waiter("waiter", "password");
            string username, password;
            cout<<"Enter waiter username: ";
            cin>>username;
            cout<<"Enter waiter password: ";
            cin>>password;

            if (user->authenticate(username, password)) {
            	
                user->menuActions(menu, tables, tableCount,takeaways,takeawayCount);
                
            } 
			else {
				
                cout<<"Authentication failed. Exiting."<<endl;
                
                delete user;
                return 1;
                
            }
        } 
		else if (userType == 3) {
			
            user = new Customer("customer", "password");
            user->menuActions(menu, tables, tableCount,takeaways,takeawayCount);
            
        } 
		else {
			
            cout<<"Invalid user type. Exiting."<<endl;
            return 1;
        }

        delete user;

    
        
        char choice;
        cout<<"Do you want to continue? (Y/N): ";
        cin >> choice;
        
        if (choice == 'N' || choice == 'n') {
            exitProgram = true;
        }
    }
//After using the dynamically allocated user object, the program deallocates the memory using delete.
	while (!exitProgram);

    return 0;
}

