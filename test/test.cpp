#ifndef _TEST_CPP
#define _TEST_CPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <functional>
#include <boost/filesystem.hpp>
#include <boost/document.hpp>
#include <boost/test/minimal.hpp>

// Negative Tests
int negative_try_opening_null() {
	try {
		boost::document d("");
		d.open_document();
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_try_opening_null Passed. Expected -- " << e.what() << std::endl;
		return 0;
	}
}

int negative_try_exporting_null() {
	try {
		boost::document d("");
		d.export_document();
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_try_exporting_null Passed. Expected -- " << e.what() << std::endl;
		return 0;
	}
}

int negative_try_closing_null() {
	try {
		boost::document d("");
		d.close_document();
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_try_closing_null Passed. Expected -- " << e.what() << std::endl;
		return 0;
	}
}

int negative_closing_unopened_document(boost::document& b) {
	try {
		b.close_document();
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_closing_unopened_document Passed. Expected -- " << e.what() << std::endl;
		return 0;
	}
}

int negative_absurd_path_opening() {
	try {
		boost::document a("./foo/bar.xls");
		a.open_document();
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_absurd_path Passed. Expected -- " << e.what() << std::endl;
		return 0;
	}
}

int negative_opening_file_without_permission(boost::document& d) {
	try {
		d.open_document();
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_opening_file_without_permission Passed. Expected -- " << e.what() << std::endl;
		return 0;
	}
}

int negative_exporting_file_without_permission(boost::document& d) {
	try {
		d.export_document();
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_opening_file_without_permission Passed. Expected -- " << e.what() << std::endl;
		return 0;
	}
}

int negative_closing_file_without_permission(boost::document& d) {
	try {
		d.close_document();
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_closing_file_without_permission Passed. Expected -- " << e.what() << std::endl;
		return 0;
	}
}

// Sheet Related Tests.
int negative_absurd_get_sheet_string(boost::document& d) {
	try {
		boost::sheet s = d.get_sheet("AbsurdSheetName");
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_get_sheet_string Passed. Expected -- " << e.what() << std::endl;
		return 0;
	}
}

int negative_absurd_get_sheet_index(boost::document& d) {
	try{
		boost::sheet s = d.get_sheet(5232);
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_get_sheet_index Passed. Expected -- " << e.what() << std::endl;
		return 0;
   }
}

// Cell Related Tests
int negative_get_invalid_cell(boost::document& d) {
	try{
		boost::sheet s = d.get_sheet(0);
		boost::cell c = s.get_cell(-1,0);
		return 1;
	}
	catch(boost::document_exception& e) {
		std::cout << "Test negative_get_invalid_cell Passed. Expected -- " << e.what() << std::endl;
		return 0;
   }
}

// Postive Tests
int create_and_save_document() {
	try{
		boost::document a("create_test1.ods");
		a.create_document();
		a.save_document();
		a.save_as_document("create_test2.ods");
		a.close_document();
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test create_and_save_document Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int exporting_to_pdf(boost::document& b) {
	try {
		b.export_document(boost::document_file_format::PDF);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test exporting_to_pdf Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int exporting_to_csv(boost::document& b) {
	try {
		b.export_document(boost::document_file_format::CSV);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test exporting_to_csv Failed." << std::endl;
		std::cerr << e.what() << std::endl;
	   return 1;
	}
}


int working_on_multiple_documents(boost::document& b, boost::document& c) {
	try {
		b.export_document(boost::document_file_format::CSV);
		c.export_document(boost::document_file_format::PDF);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test working_on_multiple_documents Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}


int get_valid_sheets(boost::document& b, boost::document& c) {
	try {
		boost::sheet s1 = c.get_sheet("Anurag"); // 1
		boost::sheet s2 = b.get_sheet(0); // "Sheet1"
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test get_valid_sheets Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int rename_valid_sheet(boost::document& b) {
	try {
		boost::sheet s1 = b.get_sheet("Anurag"); // 1
		s1.rename_sheet("Sheet2");
		BOOST_REQUIRE(s1.sheet_name() == "Sheet2");
		s1.rename_sheet("Anurag"); // Rename Back. :P
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test rename_valid_sheets Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int get_valid_sheet_count(boost::document& b) {
	try {
		BOOST_REQUIRE(b.sheet_count() == 2);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test get_valid_sheet_count Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int insert_delete_sheet_name(boost::document& b) {
	try {
		boost::sheet s1 = b.insert_sheet("Vatika");
		BOOST_REQUIRE(b.sheet_count() == 3);
		b.delete_sheet("Vatika");
		BOOST_REQUIRE(b.sheet_count() == 2);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test insert_delete_sheet_name Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int delete_sheet_index(boost::document& b) {
	try {
		boost::sheet s1 = b.insert_sheet("Vatika");
		auto idx = s1.sheet_index();
		b.delete_sheet(idx);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test delete_sheet_index Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}


int get_valid_cell_and_set_values(boost::document& b) {
	try {
		boost::sheet s = b.get_sheet(0);
		boost::cell c = s.get_cell(0,0);
		c = "Shell";
		boost::cell c1 = s.get_cell(0,1);
		c1 = 2.0;
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test get_valid_cell_and_set_values Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}


// No Exception Handling.
int sheet_and_cell_syntatic_sugar(boost::document& b,boost::document& c) {
	boost::sheet s1 = b[0];
	boost::sheet s2 = c["Anurag"];
	boost::cell cl = s2[0][0];
	s2[0][1] = "Vatika";
	s2[1][1] = "Anurag";
	BOOST_REQUIRE(s2["A2"].get_string() == "Vatika");
	return 0;
}


int negative_cell_index_check(boost::document& c) {
	boost::sheet s1 = c["Anurag"];
	try {
		s1["0A2"] = "Anurag";
		return 1;
	}
	catch(boost::document_exception& e) {
	}
	try {
		s1["A22B"] = "Anurag";
		return 1;
	}
	catch(boost::document_exception& e) {
		return 0;
	}
}

int cell_type_check(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		s1[1][1] = "Vatika";
		BOOST_REQUIRE(s1[1][1].get_content_type() == boost::cell_content_type::STRING);
		s1[1][2] = 3.14;
		BOOST_REQUIRE(s1[1][2].get_content_type() == boost::cell_content_type::VALUE);
		s1[3][4].reset();
		BOOST_REQUIRE(s1[3][4].empty() == true);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_type_check Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int cell_getters_check(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		s1[1][1] = "Vatika";
		BOOST_REQUIRE(s1[1][1].get_string() == "Vatika");
		s1[1][2] = 3.14;
		BOOST_REQUIRE(s1[1][2].get_value() < 3.15 and s1[1][2].get_value() > 3.13);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_getters_check Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}


int cell_formula_check(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		s1[2][2] = 14.6; // C3
		s1[2][3] = 5.14; // D3
		s1[2][4] = "=C3+D3";
		BOOST_REQUIRE(s1[2][4].get_content_type() == boost::cell_content_type::FORMULA);
		BOOST_REQUIRE(s1[2][4].get_value() < 19.75 && s1[2][4].get_value() > 19.73);
		BOOST_REQUIRE(s1[2][4].get_content_type() == boost::cell_content_type::FORMULA);
		BOOST_REQUIRE(s1[2][4].get_formula() == "=C3+D3");
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_formula_check Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}


int cell_reset_check(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		s1[2][2] = 14.6;
		s1[2][2].reset();
		BOOST_REQUIRE(s1[2][2].get_content_type() == boost::cell_content_type::EMPTY);
		s1[2][4].set_formula("=C3+C4");
		s1[2][4].reset();
		BOOST_REQUIRE(s1[2][4].get_content_type() == boost::cell_content_type::EMPTY);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_formula_check Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int cell_string_comparison_check(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		s1[2][2] = "Anurag";
		BOOST_REQUIRE(s1[2][2] == "Anurag");
		BOOST_REQUIRE(s1[2][2] > "Aaaaaa");
		BOOST_REQUIRE("Vatika" > s1[2][2]);
		BOOST_REQUIRE("Vatika" != s1[2][2]);
		BOOST_REQUIRE("Aaaaaa" < s1[2][2]);
		BOOST_REQUIRE(s1[2][2] < "Poland");
		s1[2][3] = "Anurag";
		BOOST_REQUIRE(s1[2][2] == s1[2][3]);
		s1[2][3] = "Vatika";
		BOOST_REQUIRE(s1[2][2] < s1[2][3]);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_string_comparison_check Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int cell_value_comparison_check(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		s1[2][2] = 1.56;
		BOOST_REQUIRE(s1[2][2] >= 1.55 && s1[2][2] <= 1.57);
		BOOST_REQUIRE(3.00 > s1[2][2]);
		BOOST_REQUIRE(3.00 != s1[2][2]);
		BOOST_REQUIRE(s1[2][2] < 3.00);
		BOOST_REQUIRE(s1[2][2] != 3.00 && s1[2][2] >= 1.00);
		BOOST_REQUIRE(1.00 < s1[2][2]);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_value_comparison_check Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int cell_formula_comparison_check(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		s1[2][2] = 1.00; // C3
		s1[2][3] = 0.56; // D3
		s1[2][4] = "=C3+D3";
		s1[2][5] = "=C3+D3";
		BOOST_REQUIRE(s1[2][4] >= 1.55 && s1[2][4] <= 1.57);
		BOOST_REQUIRE(1.00 < s1[2][4]);
		BOOST_REQUIRE(s1[2][5] == s1[2][4]);
		BOOST_REQUIRE(s1[2][4] < 3.00);
		BOOST_REQUIRE(s1[2][4] <= 3.00 && s1[2][4] > 1.00);
		BOOST_REQUIRE(s1[2][4] == "=C3+D3");
		BOOST_REQUIRE("=C3+D4" != s1[2][5]);
		BOOST_REQUIRE("=C3+D3" == s1[2][5]);
		BOOST_REQUIRE(1.55 <= s1[2][5]);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_formula_comparison_check Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}


int cell_generic_comparison_check(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		s1[2][2] = 1.00; // C3
		s1[2][3] = "Vatika"; // D3
		s1[2][4] = 1.44;
		BOOST_REQUIRE(s1[2][2] != s1[2][4]);
		BOOST_REQUIRE(s1[2][2] < s1[2][4]);
		BOOST_REQUIRE(s1[2][2] <= s1[2][4]);
		// different types involved
		BOOST_REQUIRE(s1[2][3] != 1.45);
		BOOST_REQUIRE(s1[2][2] == s1[2][2]);
		BOOST_REQUIRE(!(s1[2][2] != s1[2][2]));
		BOOST_REQUIRE(s1[2][2] != s1[2][3]);
		BOOST_REQUIRE(s1[2][2] <= s1[2][3]);
		BOOST_REQUIRE(s1[2][3] > s1[2][2]);
		s1[2][2] = 3.14159;
		BOOST_REQUIRE(3.14159 == s1[2][2] || 3.14158 <= s1[2][2] || 3.14160 >= s1[2][2]);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_generic_comparison_check Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}


int check_row_and_column_class(boost::document& c) {
	try {

		boost::sheet s1 = c["Anurag"];

		boost::row r = s1.get_row(3);
		r[4] = "Anurag";
		BOOST_REQUIRE(s1[4][3].get_string() == "Anurag");

		boost::column l = s1.get_column(9);
		l[2] = "Vatika";
		BOOST_REQUIRE(s1[9][2].get_string() == "Vatika");

		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test check_row_and_column_class Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int check_for_sheet_and_row_scope(boost::document& c) {
	try {
		boost::sheet s = c["Anurag"];
		boost::row r = s.get_row(10);
		r[20] = "Hello world";
		boost::column k = s.get_column(20);

		s = c[0]; // ... new sheet is used instead of the old one
		// s is now out of scope.
		// if r and c had raw pointers of s,
		// then seg fault can occur.
		BOOST_REQUIRE(r[20].get_string() == k[10].get_string());
		BOOST_REQUIRE(k[10].get_string() == "Hello world");

		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test check_for_sheet_and_row_scope Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int row_iterator_comparison(boost::document& c) {
	try {
		boost::sheet s1 = c.get_sheet(0);
		boost::sheet s2 = c.get_sheet(0);
		boost::sheet s_different = c.get_sheet(1);
		boost::row r1 = s1.get_row(3);
		boost::row r2 = s2.get_row(3);
		boost::row r_different = s_different.get_row(3);
		boost::row r_different2 = s2.get_row(4);
		//assert(r1 == r2); // same rows from same sheets, but sheet pointers differ
		//assert(r1 != r_different); // sheets differ
		//assert(r1 != r_different2); // rows differ
		//assert(r2 != r_different2); // rows differ
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test row_iterator_comparison Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int use_row_iterator(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		boost::row r = s1.get_row(3);
		for(auto k = r.begin(); k != r.begin() + 20; k++) {
		  *k = 1;
		}
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test use_row_iterator Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int row_stl_functionality(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		boost::row r = s1.get_row(3);
		std::fill(r.begin(), r.begin() + 50, 1);
		double sum = 0;
		const boost::row_iterator end(r.begin() + 50);
		for (auto it = r.begin(); it != end; ++it) {
			sum += (*it).get_value();
		}
		BOOST_REQUIRE(sum < 50.1 && sum > 49.9);
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test row_stl_functionality Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int cell_swap_test(boost::document& c) {
	try {
		using std::swap;
		boost::sheet s1 = c["Anurag"];
		s1[2][2] = "Anurag";
		s1[2][3] = "Vatika";
		swap(s1[2][2], s1[2][3]);
		BOOST_REQUIRE(s1[2][3] == "Anurag" && s1[2][2] == "Vatika" && s1[2][3].get_content_type() == boost::cell_content_type::STRING);
		s1[2][2] = "=C2+D2";
		s1[2][3] = "=C2+D3";
		swap(s1[2][2], s1[2][3]);
		BOOST_REQUIRE(s1[2][3] == "=C2+D2" && s1[2][2] == "=C2+D3" && s1[2][2].get_content_type() == boost::cell_content_type::FORMULA);
		s1[2][2] = "=C2+D2";
		s1[2][3] = "Vatika";
		swap(s1[2][2], s1[2][3]);
		BOOST_REQUIRE(s1[2][2] == "Vatika" && s1[2][3] == "=C2+D2" &&
					s1[2][3].get_content_type() == boost::cell_content_type::FORMULA &&
				  s1[2][2].get_content_type() == boost::cell_content_type::STRING);
		s1[2][2] = 1.23;
		s1[2][3] = 2.13;
		swap(s1[2][2], s1[2][3]);
		BOOST_REQUIRE(s1[2][3] <= 1.24 && s1[2][3] >= 1.22
									&& s1[2][2] >= 2.12 && s1[2][2] <= 2.14);
		s1[2][3] = 2.13;
		s1[2][2].reset();
		swap(s1[2][3],s1[2][2]);
		BOOST_REQUIRE(s1[2][2] >= 2.12 && s1[2][2] <= 2.14 &&
						s1[2][3].get_content_type() == boost::cell_content_type::EMPTY &&
						s1[2][2].get_content_type() == boost::cell_content_type::VALUE);
		return 0;
	}
	catch(boost::document_exception& e) {
			std::cerr << "Test cell_swap_test Failed." << std::endl;
			std::cerr << e.what() << std::endl;
			return 1;
	}
}


template<typename T>
void insertion_sort(T& r, int len) {
		for(int i=0; i<len; i++) {
				int j = i;
				while(j > 0 and r[j] < r[j-1]) {
						swap(r[j],r[j-1]);
						j--;
				}
		}
}

/*template <class CellArray>
void quick_sort(CellArray first, CellArray last) {
    if(first == last) return;
    auto pivot = *std::next(first, std::distance(first,last)/2);
    CellArray middle1 = std::partition(first, last,
                         [pivot](const auto& em){ return em < pivot; });
    CellArray middle2 = std::partition(middle1, last,
                         [pivot](const auto& em){ return !(pivot < em); });
    quick_sort(first, middle1);
    quick_sort(middle2, last);
}*/


int row_double_sort_test(boost::document& c) {
	try {
			using std::swap;
			boost::sheet s1 = c["Anurag"];
			boost::row r = s1.get_row(3);
			std::random_device rnd_device;
			std::mt19937 mersenne_engine(rnd_device());
			std::uniform_real_distribution<double> dist(1,5);
			int len = 50;
			auto gen = std::bind(dist, mersenne_engine);
			std::generate(r.begin(), r.begin() + len, gen);
			boost::row_iterator end(r.begin() + len);
			// A simple insertion sort implementation
			insertion_sort(r, len);
			//std::stable_sort(r.begin(), end);
			//std::sort(r.begin(), end);
			std::cout << std::endl;
			BOOST_REQUIRE(std::is_sorted(r.begin(),end));
			return 0;
	}
	catch(boost::document_exception& e) {
			std::cerr << "Test row_double_sort_test Failed." << std::endl;
			std::cerr << e.what() << std::endl;
			return 1;
	}
}

int row_string_sort_test(boost::document& c) {
	try {
			using std::swap;
			boost::sheet s1 = c["Anurag"];
			boost::row r = s1.get_row(3);
			std::random_device rnd_device;
			std::mt19937 mersenne_engine(rnd_device());
			std::uniform_real_distribution<double> dist(1,50);
			auto gen = std::bind(dist, mersenne_engine);
			int len = 50;
			std::generate(r.begin(), r.begin() + len, gen);
			boost::row_iterator end(r.begin() + len);
			// A simple insertion sort implementation
			insertion_sort(r, len);
			// std::stable_sort(r.begin(), end);
			BOOST_REQUIRE(std::is_sorted(r.begin(),end));
			return 0;
	}
	catch(boost::document_exception& e) {
			std::cerr << "Test row_string_sort_test Failed." << std::endl;
			std::cerr << e.what() << std::endl;
			return 1;
	}
}

int column_heterogenous_sort_test(boost::document& c) {
	try {
			using std::swap;
			boost::sheet s1 = c["Anurag"];
			boost::column cl = s1.get_column(3);
			int len = 6;
			cl[0] = "0qweqwe";
			cl[1] = 100.1;
			cl[2] = "1HelloWorld";
			cl[3].reset();
			cl[4] = 1.2;
			cl[5] = 3132.0;
			cl[6] = 0.0;
			boost::column_iterator end(cl.begin() + len);
			//quick_sort(cl.begin(), end);
			insertion_sort(cl, len);
			BOOST_REQUIRE(std::is_sorted(cl.begin(),end));
			return 0;
	}
	catch(boost::document_exception& e) {
			std::cerr << "Test column_heterogenous_sort_test Failed." << std::endl;
			std::cerr << e.what() << std::endl;
			return 1;
	}
}

int row_lower_bound_test(boost::document& c) {
	try {
			boost::sheet s1 = c["Anurag"];
			boost::row r = s1.get_row(7);
			const boost::row_iterator end(r.begin() + 12);
			std::fill(r.begin(), r.begin() + 2, 1);
			std::fill(r.begin() + 2, r.begin() + 4, 4);
			std::fill(r.begin() + 4, r.begin() + 6, 6);
			std::fill(r.begin() + 6, r.begin() + 8, 2);
			std::fill(r.begin() + 8, r.begin() + 10, 5);
			std::fill(r.begin() + 10, r.begin() + 12, 3);
			for (auto it = r.begin(); it != end; ++it) {
				std::cout << (*it).get_value() << std::endl;
			}
			std::nth_element(r.begin(), r.begin() + 6, r.begin() + 12);
			for (auto it = r.begin(); it != end; ++it) {
				std::cout << (*it).get_value() << std::endl;
			}
			BOOST_REQUIRE(1==1);
			return 0;
	}
	catch(boost::document_exception& e) {
			std::cerr << "Test row_lower_bound_test Failed." << std::endl;
			std::cerr << e.what() << std::endl;
			return 1;
	}
}

int column_bin_search_test(boost::document& c) {
	try {
			boost::sheet s1 = c["Anurag"];
			boost::column r = s1.get_column(7);
			const boost::column_iterator end(r.begin() + 100);
			auto i = 0;
			for (auto it = r.begin(); it != end; ++it) {
					*it = i;
					i += 1;
			}
			auto x = std::binary_search(r.begin(), end, 56);
			BOOST_REQUIRE(x==true);
			x = std::binary_search(r.begin(), end, 134);
			BOOST_REQUIRE(x==false);
			for (auto it = r.begin(); it != end; ++it) {
					it->reset();
			}
			return 0;
	}
	catch(boost::document_exception& e) {
			std::cerr << "Test column_bin_search_test Failed." << std::endl;
			std::cerr << e.what() << std::endl;
			return 1;
	}
}

int row_iterator_caching(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		boost::cell c1 = s1[0][0];
		c1 = "Anurag";
		boost::column_iterator it = s1[0].begin();
		assert((*it).get_string() == c1.get_string());
		c1 = "Vatika"; // changed the cell value!
		assert((*it).get_string() == c1.get_string()); // Iterator should reflect the same. :)
		// It does reflect because the operations are write through.
		// there are no operations which are locally performed in the instance
		// and delegated for later. All operations are final in nature.
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test row_iterator_caching Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int cell_format_test(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		boost::cell c1 = s1[0][0];
		c1.set_foreground_color(0x800000);
		c1.set_background_color(0x00800b);
		c1.set_style("Heading1");
		boost::cell c2 = s1[0][1];
		c2.set_foreground_color(0x800000);
		c2.set_font_size(18);
		c2.set_vertical_alignment(boost::cell_vertical_alignment::TOP);
		c2.set_horizontal_alignment(boost::cell_horizontal_alignment::RIGHT);
		c.export_document( boost::filesystem::path("Test2_style.pdf"), boost::document_file_format::PDF); // to check the output, basically
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_format_test Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int cell_border_test(boost::document& c) {
	try {
		boost::sheet s1 = c["Anurag"];
		boost::cell c1 = s1[1][0];
		boost::cell c2 = s1[1][1];
		boost::cell c3 = s1[1][2];
		c1.set_border(boost::cell_border_style::CONTINUOUS, boost::cell_border_weight::MEDIUM, 0x000000);
		c2.set_border(boost::cell_border_style::DASHDOT, boost::cell_border_weight::THICK, 0x800000);
		c3.set_border(boost::cell_border_style::DASH, boost::cell_border_weight::THIN, 0x00800b);
		c.export_document( boost::filesystem::path("Test2_style1.pdf"), boost::document_file_format::PDF); // to check the output, basically
		return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test cell_border_test Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int basic_chart_test(boost::document& c) {
	try {
			boost::sheet s1 = c.insert_sheet("ChartTest");

			// Example Adapted from http://api.libreoffice.org/examples/java/Spreadsheet/SCalc.java
			s1[0][1] = "JAN";
			s1[0][2] = "FEB";
			s1[0][3] = "MAR";
			s1[0][4] = "APR";
			s1[0][5] = "MAY";
			s1[0][6] = "JUN";
			s1[0][7] = "JUL";
			s1[0][8] = "AUG";
			s1[0][9] = "SEP";
			s1[0][10] = "OCT";
			s1[0][11] = "NOV";
			s1[0][12] = "DEC";
			s1[0][13] = "SUM";

			s1[1][0] = "Smith";
			s1[1][1] = 42;
			s1[1][2] = 58.9;
			s1[1][3] = -66.5;
			s1[1][4] = 43.4;
			s1[1][5] = 44.5;
			s1[1][6] = 45.3;
			s1[1][7] = -67.3;
			s1[1][8] = 30.5;
			s1[1][9] = 23.2;
			s1[1][10] = -97.3;
			s1[1][11] = 22.4;
			s1[1][12] = 23.5;
			s1[1][13] = "=SUM(B2:M2)";

			s1[2][0] = "Jones";
			s1[2][1] = 21;
			s1[2][2] = 40.9;
			s1[2][3] = -57.5;
			s1[2][4] = -23.4;
			s1[2][5] = 34.5;
			s1[2][6] = 59.3;
			s1[2][7] = 27.3;
			s1[2][8] = -38.5;
			s1[2][9] = 43.2;
			s1[2][10] = 57.3;
			s1[2][11] = 25.4;
			s1[2][12] = 28.5;
			s1[2][13] = "=SUM(B3:M3)";

			s1[3][0] = "Brown";
			s1[3][1] = 31.45;
			s1[3][2] = -20.9;
			s1[3][3] = -117.5;
			s1[3][4] = 23.4;
			s1[3][5] = -114.5;
			s1[3][6] = 115.3;
			s1[3][7] = -171.3;
			s1[3][8] = 89.5;
			s1[3][9] = 41.2;
			s1[3][10] = 71.3;
			s1[3][11] = 25.4;
			s1[3][12] = 38.5;
			s1[3][13] = "=SUM(B4:M4)";

			boost::chart chrt = s1.add_chart("Test1", "A1:N4", 500, 3000, 25000, 11000, boost::chart_type::PIE);
			c.export_document( boost::filesystem::path("Test2_chart1.pdf"), boost::document_file_format::PDF); // to check the output, basically
			s1.delete_chart("Test1");
			c.save_as_document(boost::filesystem::path("Test2_chart1.ods"));
			return 0;
	}
	catch(boost::document_exception& e) {
		std::cerr << "Test basic_chart_test Failed." << std::endl;
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

int test_main(int argc, char *argv[]) {
//#ifdef BOOST_DOCUMENT_HAS_MS
//    boost::document b("Excel_Test1.xlsx");
//    boost::document d("Excel_Test2.xlsx");
//    boost::document c("Excel_Test3.xlsx");
//#elif defined(BOOST_DOCUMENT_HAS_LIBRE)
	boost::document b("Test1.ods");
	boost::document c("Test2.ods");
	boost::document d("Test3.ods");
//#else
//#endif

	int rv = 0;


	// Sanity Checks
	rv += negative_try_opening_null();
	rv += negative_try_exporting_null();
	rv += negative_try_closing_null();
	rv += negative_closing_unopened_document(b);
	rv += negative_absurd_path_opening();

	// Permissions related checks
	rv += negative_opening_file_without_permission(d);
	rv += negative_exporting_file_without_permission(d);
	rv += negative_closing_file_without_permission(d);

	b.open_document();
	c.open_document();


	rv += negative_absurd_get_sheet_string(b);
	rv += negative_absurd_get_sheet_index(b);

	rv += negative_get_invalid_cell(b);

	// Positive Checks
	rv += create_and_save_document();
	rv += exporting_to_pdf(b);
	rv += exporting_to_csv(b);
	rv += working_on_multiple_documents(b,c);
	rv += get_valid_sheets(b,c);
	rv += rename_valid_sheet(c);
	rv += get_valid_sheet_count(c);
	rv += insert_delete_sheet_name(c);
	rv += delete_sheet_index(b);

	// Cell related checks
	rv += get_valid_cell_and_set_values(b);
	rv += sheet_and_cell_syntatic_sugar(b,c);
	rv += cell_type_check(c);
	rv += cell_getters_check(c);
	rv += cell_formula_check(c);
	rv += cell_reset_check(c);
	rv += negative_cell_index_check(c);

	// Comparison's check
	rv += cell_string_comparison_check(c);
	rv += cell_value_comparison_check(c);
	rv += cell_formula_comparison_check(c);
	rv += cell_generic_comparison_check(c);

	// iterator checks
	rv += check_row_and_column_class(c);
	rv += check_for_sheet_and_row_scope(c);
	rv += row_iterator_caching(c);
	rv += row_iterator_comparison(c);

	rv += use_row_iterator(c);
	rv += row_stl_functionality(c);
	rv += cell_swap_test(c);
	rv += row_double_sort_test(c);
	rv += row_string_sort_test(c);
	rv += column_heterogenous_sort_test(c);
	rv += row_lower_bound_test(c);
	rv += column_bin_search_test(c);

	rv += cell_format_test(c);
	rv += cell_border_test(c);

	rv += basic_chart_test(c);

	if (rv > 0) {
		std::cout << rv << " Tests Failed. Look at Log for more information." << std::endl;
	}
	return rv;
}

#endif
