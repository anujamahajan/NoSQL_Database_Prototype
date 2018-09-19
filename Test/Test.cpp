///////////////////////////////////////////////////////////////////////
// Test.cpp - provides test cases for NoSQL database prototype       //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Anuja Mahajan, Syracuse University(MSCS-Spring 2018) //
//				apmahaja@syr.edu									 //
///////////////////////////////////////////////////////////////////////

#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Query/Query.h"
#include "../DateTime/DateTime.h"
#include "Test.h"

///////////////////////////////////////////////////////////////////////
// DbProvider class
// - provides mechanism to share a test database between test functions
//   without explicitly passing as a function argument.

class DbProvider
{
public:
	DbCore<Payload>& db() { return db_; }
private:
	static DbCore<Payload> db_;
};

DbCore<Payload> DbProvider::db_;

//----< reduce the number of characters to type >----------------------
auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
{
	Utilities::putline(n, out);
};

///////////////////////////////////////////////////////////////////////
// Test functions demonstarting requirements

//----< demo requirement #1 >------------------------------------------
bool testR1()
{
	Utilities::title("Demonstrating Requirement #1");
	std::cout << "\n  " << typeid(std::function<bool()>).name()
		<< ", declared in this function, "
		<< "\n  is only valid for C++11 and later versions.";
	putLine();
	return true; // would not compile unless C++11
}

//----< demo requirement #2 >------------------------------------------
bool testR2()
{
	Utilities::title("Demonstrating Requirement #2");
	std::cout << "\n  A visual examination of all the submitted code "
		<< "will show only\n  use of streams and operators new and delete.";
	putLine();
	return true;
}

//----< demo first part of requirement #3- creating database element >----------------------------
bool testR3a()
{
	Utilities::title("Demonstrating Requirement #3a and #4a- creating DbElement and adding into database");
	std::cout << "\n  Creating a db element with key \"Fawcett\":";
	// create database to hold payload object
	DbCore<Payload> db;
	DbProvider dbp;
	// create some demo elements and insert into db
	std::string filepath = "DbCore";
	std::vector<std::string> categories = { "DbCore","Query1","Utility" };
	Payload p(filepath, categories);
	DbElement<Payload> dbElem;
	dbElem.name("J.");
	dbElem.descrip("CSE687");
	dbElem.dateTime(DateTime().now());
	dbElem.payLoad(p);
	db["Fawcett"] = dbElem;
	showHeader();
	showElem("Fawcett", dbElem);
	dbp.db() = db;
	putLine(2);
	std::unordered_map<std::string, DbElement<Payload>>::iterator it = db.dbStore().find("Fawcett");
	if (it == db.dbStore().end())
		return false;
	else
	{
		return true;
	}
}
//----< demo second part of requirement #3- creating database >---------------------------
bool testR3b()
{
	Utilities::title("Demonstrating Requirement #3b- creating DbCore");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	string originalFile = "../originalDB.xml";
	//If xml exists build database from xml or else create it
	if (isFileExists(originalFile)) {
		cout << "\n  Building Database from XML";
		createDBFromXML(originalFile, db);
	}
	else {
		cout << "\n  Creating Database";
		DbElement<Payload> dbElem;
		dbElem.name("Ammar");
		dbElem.descrip("TA for CSE687");
		dbElem.dateTime(DateTime().now());
		db["DateTime"] = dbElem;

		dbElem.name("Jianan");
		dbElem.descrip("Grad student");
		vector<string> categories = { "DbCore","Query","Test" };
		Payload p("Query.cpp", categories);
		dbElem.payLoad(p);
		dbElem.dateTime(DateTime("Mon Jan 16 12:12:12 2018"));
		db["Sun"] = dbElem;

		dbElem.descrip("Graduating");
		p.filePath("Test.cpp");
		dbElem.payLoad(p);
		dbElem.name("Nikhil");
		dbElem.dateTime(DateTime("Tue Jan 21 12:00:00 2018"));
		db["Prashar"] = dbElem;

		vector<string> c = { "Db","Test","Test2" };
		p.categories(c);
		dbElem.payLoad(p);
		dbElem.name("Pranjul");
		dbElem.descrip("TA 2018");
		dbElem.dateTime(DateTime("Mon Jan 05 00:00:00 2018"));
		db["Arora"] = dbElem;

		p.addCategories("Test3");
		dbElem.payLoad(p);
		dbElem.name("Prakash");
		dbElem.descrip("TA for CSE687");
		db["Anjanappa"] = dbElem;

		dbElem.payLoad(p);
		dbElem.name("Pooja");
		dbElem.descrip("TA for Fall");
		db["Soni"] = dbElem;

		c = { "Test","Test2" };
		p.categories(c);
		dbElem.payLoad(p);
		dbElem.name("Priya");
		dbElem.descrip("blah blah");
		db["A"] = dbElem;
		if (!db["Fawcett"].isEmpty()) {
			db["Fawcett"].children().push_back("Salman");
			db["Fawcett"].children().push_back("Sun");
			db["Fawcett"].children().push_back("Prashar");
			db["Fawcett"].children().push_back("Arora");
			db["Fawcett"].children().push_back("Anjanappa");
			db["Fawcett"].children().push_back("Soni");
			db["Fawcett"].children().push_back("A");
		}
		if (!db["Salman"].isEmpty()) {
			db["Salman"].children().push_back("Sun");
			db["Salman"].children().push_back("Prashar");
			db["Salman"].children().push_back("Arora");
			db["Salman"].children().push_back("Anjanappa");
		}
		//save db in XML file
		std::cout << "\n  Saving database to XML file";
		dbp.db() = db;
		db.saveDB(originalFile);
		return true;
	}
	// display the results
	dbp.db() = db;
	std::cout << "\n  Showing all the database elements:";
	showDb(db);
	putLine();
	return true;
}

//----< demo requirement #4- deletion of key value pair >---------------------------
bool testR4b()
{
	Utilities::title("Demonstrating Requirement #4b - deletion of key-value pair");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	std::string key = "Soni";
	std::cout << "\n  Number of elements in database before deleting: " << db.size();
	std::cout << "\n  Deleting key: " << key;
	std::unordered_map<std::string, DbElement<Payload>>& dbStore = db.dbStore();
	std::unordered_map<std::string, DbElement<Payload>>::iterator it = dbStore.find(key);
	if (it == dbStore.end()) {
		std::cout << "\n  Key " << key << "does not exist in database";
		return false;
	}
	else {
		dbStore.erase(key);
		dbStore.reserve(dbStore.size());
	}
	std::cout << "\n  Number of elements in database after deleting: " << db.size();
	// display the results
	putLine();
	dbp.db() = db;
	putLine();
	return true;
}

//----< demo requirement #5- addition of children>---------------------------
bool testR5a()
{
	Utilities::title("Demonstrating Requirement #5a - addition of children");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	std::string childKey = "ABC";
	DbElement<Payload> dbElement;
	string s = "Utility";
	vector<string> c = { "DbCore","Utilities" };
	Payload p(s, c);
	dbElement.name("XYZ");
	dbElement.descrip("Internation student..");
	dbElement.payLoad(p);
	dbElement.dateTime(DateTime().now());
	db[childKey] = dbElement;

	std::cout << "\n  Add children into key \"Sun\" ";
	std::string parentKey = "Sun";
	std::unordered_map<std::string, DbElement<Payload>>& dbStore = db.dbStore();
	std::unordered_map<std::string, DbElement<Payload>>::iterator it = dbStore.find(parentKey);
	if (it == dbStore.end()) {
		std::cout << "\n  Key " << parentKey << "does not exist in database";
		return false;
	}
	else {
		std::vector<std::string> children = db[parentKey].children();
		std::vector<std::string>::iterator position = std::find(children.begin(), children.end(), childKey);
		if (position == children.end()) {
			db[parentKey].children().push_back(childKey);
			std::cout << "\n  Children added in " << parentKey;
		}
		else {
			std::cout << "\n  Children " << childKey << " already added in " << parentKey;
		}
	}
	dbp.db() = db;
	// display the results
	putLine(2);
	return true;
}

//----< demo requirement #5- deletion of children>---------------------------
bool testR5b()
{
	Utilities::title("Demonstrating Requirement #5b - deletion of children");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	std::string parentKey = "Salman";
	std::string childKey = "Sun";
	std::cout << "\n  Delete child with key " << childKey << " from parent " << parentKey;
	std::unordered_map<std::string, DbElement<Payload>>& dbStore = db.dbStore();
	std::unordered_map<std::string, DbElement<Payload>>::iterator it = dbStore.find(parentKey);

	if (it == dbStore.end())
		std::cout << "\n  Key " << parentKey << " does not exist in database";
	else
	{
		DbElement<Payload>::Children& children = it->second.children();
		std::vector<std::string>::iterator it1;
		if (!children.empty()) {
			it1 = std::find(children.begin(), children.end(), childKey);
			if (it1 != children.end()) {
				std::cout << "\n  Child with key " << childKey << " present, hence deleting it";
				children.erase(it1);
				children.reserve(children.size());
			}
			else {
				std::cout << "\n  Child with key " << childKey << " does not exist in: " << it->first;
			}
		}
	}
	dbp.db() = db;
	std::cout << "\n  showing all the database elements:";
	showDb(db);
	putLine(2);
	return true;
}

//----< demo requirement #5c- editing text metadata>---------------------------
bool testR5c()
{
	Utilities::title("Demonstrating Requirement #5c - editing text metadata");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	std::string key = "Fawcett";
	std::unordered_map<std::string, DbElement<Payload>>& dbStore = db.dbStore();
	std::unordered_map<std::string, DbElement<Payload>>::iterator it = dbStore.find(key);
	if (it == dbStore.end())
		std::cout << "\n  Key " << key << " does not exist in database";
	else {
		vector<string> c = { "Utiities" };
		Payload p("xyz..", c);
		it->second.name("J.");
		it->second.descrip("jfawcett@twcny.rr.com");
		it->second.children().push_back("ABC");
		it->second.payLoad().categories(c);
		std::cout << "\n  Element with " << key << " after editing text metadata";
		showHeader();
		showElem(key, it->second);
	}
	dbp.db() = db;
	putLine(2);
	return true;
}

//----< demo requirement #5d- replacing existing element>---------------------------
bool testR5d()
{
	Utilities::title("Demonstrating Requirement #5d - Replacing existing element");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	std::string key = "ABC";
	std::unordered_map<std::string, DbElement<Payload>>& dbStore = db.dbStore();
	std::unordered_map<std::string, DbElement<Payload>>::iterator it = dbStore.find(key);
	if (it == dbStore.end())
		std::cout << "\n  Key " << key << " does not exist in database";
	else {
		DbElement<Payload> element;
		std::vector<std::string> v = { "Executive","XML" };
		Payload p("test123.cpp", v);
		element.name("PQR");
		element.descrip("TA joining in spring 2018");
		element.dateTime(DateTime("Mon Jan 16 00:00:00 2018"));
		element.payLoad(p);
		db[key] = element;
		std::cout << "\n Element with key " << key << " after replacing";
		showElem(key, element);
	}
	dbp.db() = db;
	putLine(2);
	return true;
}

//----< demo requirement #6a Query to find value of specified key>---------------------------
bool testR6a()
{
	Utilities::title("Demonstrating Requirement #6a - Query to find value of the specified key");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	std::string key = "ABC";
	cout << "\n  Value of Key: " << key;
	Query<Payload> query(db);
	query.getValue(key).show();
	putLine(2);
	return true;
}

//----< demo requirement #6b Query to find children of specified key>---------------------------
bool testR6b()
{
	Utilities::title("Demonstrating Requirement #6b - Query to find children of the specified key");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	std::string key = "Fawcett";
	cout << "\n  Showing children of " << key;
	Query<Payload> query(db);
	query.getChildren(key).show();
	putLine(2);
	return true;
}

//----< demo requirement #6c Query to find all keys matching with specified regex>---------------------------
bool testR6c()
{
	Utilities::title("Demonstrating Requirement #6c - Query to find all keys matching with specified regular expression");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	Query<Payload> query(db);
	Condition cond;
	regex regEx("(A)(.*)");
	cout << "\n  Matching regex \"(A)(.*)\" with all keys";
	cond.setKeyRegex(regEx);
	query.select(cond).show();
	putLine(2);
	return true;
}

//----< demo requirement #6d Query to find metadata matching with specified regex>---------------------------
bool testR6d()
{
	Utilities::title("Demonstrating Requirement #6d - Query to find metadata matching with specified regular expression");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	Query<Payload> query(db);
	Condition cond;
	regex nameRegEx("(P[rQ])(.*)");
	regex descrpRegEx("(TA)(.*)");
	regex categoryRegEx(".*\\d+.*");
	cout << "\n  Matching regex \"(P[rQ])(.*)\" with name, \"(TA)(.*)\" with description,\".*\\d+.*\" with payload categories of all keys ";
	cond.setNameRegex(nameRegEx).setDescriptionRegex(descrpRegEx).setCategoryRegExp(categoryRegEx);
	query.select(cond).show();
	putLine();
	return true;
}

//----< demo requirement #6e Query to find keys within specified time interval>---------------------------
bool testR6e()
{
	Utilities::title("Demonstrating Requirement #6e - Query to find keys within specified time interval");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	Query<Payload> query(db);
	Condition cond;
	DateTime date1("Mon Jan 06 00:00:00 2018");
	DateTime date2("Mon Jan 25 00:00:00 2018");
	cout << "\n  From : " << date1.time() << "- To: " << date2.time();
	cond.setDateTime(date1, date2);
	query.select(cond).show();
	putLine(2);
	return true;
}

//----< demo requirement #6f Query to find keys within specified time interval, (only one date is given)>--------------
bool testR6f()
{
	Utilities::title("Demonstrating Requirement #6e - Query to find keys within specified time and current date");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	Query<Payload> query(db);
	Condition cond;
	DateTime date1("Mon Jan 16 00:00:00 2018");
	cout << "\n  From/To : " << date1.time() << "- Current time";
	cond.setFromOrToDate(date1);
	query.select(cond).show();
	putLine(2);
	return true;
}

//----< demo requirement #7a- Support for querying on key result of previous query>--------------
bool testR7a()
{
	Utilities::title("Demonstrating Requirement #7a - support queries on the set of keys returned by a previous query");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	Query<Payload> query1(db);
	Query<Payload> query2(db);
	Query<Payload> resultQuery(db);
	Condition cond1, cond2;
	regex descrpRegEx("(TA)(.*)");
	regex keyRegEx("(A)(.*)");
	regex nameRegEx("(P[r])(.*)");
	cond1.setDescriptionRegex(descrpRegEx);
	cond2.setKeyRegex(keyRegEx);
	cout << "\n  Performing Query1 (description starting with \"TA\"): ";
	query1.select(cond1).show();
	putLine();
	cout << "\n  Performing Query2 (key with \"A\")";
	query2.select(cond2).show();
	putLine();
	cout << "\n  Performing Query2 on set of keys from Query1 (AND): ";
	resultQuery.select(cond1).select(cond2).show();
	putLine(2);
	return true;
}

//----< demo requirement #7b- Support for querying on union result of one or more queries>--------------
bool testR7b()
{
	Utilities::title("Demonstrating Requirement #7b - support queries on the union of results of one or more previous queries");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	Query<Payload> query1(db), query2(db), resultQuery(db);
	Condition cond1, cond2;
	regex keyRegEx("(A)(.*)");
	regex nameRegEx("(J)(.*)");
	cond1.setKeyRegex(keyRegEx);
	cout << "\n  Performing Query1 ( key starting with \"A\")";
	query1.select(cond1).show();
	cond2.setNameRegex(nameRegEx);
	cout << "\n  Performing Query2: ( name starting with \"J\"";
	query2.select(cond2).show();
	cout << "\n  Performing Union of query1 and query2 (OR operation)";
	resultQuery.select(cond2).from(query1.keys()).show();
	putLine();
	return true;
}

//----< demo requirement #8a- Persistence of the database to XML file>--------------
bool testR8a()
{
	Utilities::title("Demonstrating Requirement #8a - Save database to XML file");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	std::string xml = db.saveDB("../modifiedDB.xml");
	cout << "\n  Database stored in xml : \n  " << xml;
	putLine(2);
	return true;
}

//----< demo requirement #8b- Restoring database from XML file>--------------
bool testR8b()
{
	Utilities::title("Demonstrating Requirement #8b - Restore database from XML file");
	DbCore<Payload> db;
	createDBFromXML("../OriginalDB.xml", db);
	showDb(db);
	putLine(2);
	return true;
}