#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> to_words(string sentnce)
{
	vector<string> words = {};

	int i = 0,
		j, len = sentnce.length(), x;
	char *temp;
	string word;

	while (i < len)
	{

		while (sentnce[i] == ' ')
		{
			i++;
		}

		j = i;

		while (sentnce[i] != ' ' && i < len)
		{
			i++;
		}

		x = i - j;

		temp = new char(x);
		word = "";

		for (int e = 0; e < x; e++)
		{
			word += sentnce[j + e];
		}

		words.push_back(word);
	}

	return words;
}

vector<int> word_lens(vector<string> word_list)
{
	vector<int> X = {};
	int len = word_list.size();

	for (int i = 0; i < len; i++)
	{
		X.push_back(word_list[i].size());
	}

	return X;
}

int words_per_line(vector<int> word_lens)
{

	const float ratio = 8.0;
	int len = word_lens.size();
	float min_diff = 20.0, diff;
	int x, y, words_in_a_line;

	for (int i = 0; i < len / 2 + 1; i++)
	{

		x = 0;
		y = len / (i + 1);
		if (len % (i + 1) != 0)
		{
			y++;
		}

		for (int e = 0; e < i; e++)
		{
			x += word_lens[e];
		}

		diff = ratio - ((float)x / (float)y);
		if (diff < 0)
			diff *= -1;
		if (diff < min_diff)
		{
			min_diff = diff;
			words_in_a_line = i;
		}
	}

	return words_in_a_line;
}

vector<vector<string>> get_ordered_string(string sentence)
{
	vector<string> word_list = to_words(sentence);
	int len = word_list.size();
	int wpl = words_per_line(word_lens(word_list));

	vector<vector<string>> sets{};
	vector<string> set = {};

	int i = 0;
	while (i < len)
	{
		for (int e = 0; e < wpl && i < len; e++)
		{
			set.push_back(word_list[i++]);
		}
		sets.push_back(set);
		set.clear();
	}

	return sets;
}

vector<int> char_per_line(vector<vector<string>> sets)
{

	vector<int> cpl = {};

	int m_len = 0, temp;
	int len = sets.size();
	for (int i = 0; i < len; i++)
	{

		temp = 0;
		for (int e = 0; e < sets[i].size(); e++)
		{
			if (e != 0)
				temp += 1;
			temp += sets[i][e].size();
		}

		cpl.push_back(temp);
	}
	return cpl;
}

int max_len(vector<vector<string>> sets)
{

	int m_len = 0, temp;
	vector<int> cpl = char_per_line(sets);
	int len = cpl.size();

	for (int i = 0; i < len; i++)
	{
		temp = cpl[i];
		m_len = (temp > m_len) ? temp : m_len;
	}
	return m_len;
}

void printer(vector<vector<string>> sets)
{
	int columns = max_len(sets) + 12;
	for (int t = 0; t < 2; t++)
	{
		for (int i = 0; i < columns; i++)
		{
			cout << "*";
		}
		cout << "\n";
	}

	vector<int> cpl = char_per_line(sets);
	int lines = cpl.size();
	int in_stars = 0, w_len;

	for (int i = 0; i < lines; i++)
	{
		in_stars = (columns - cpl[i]);
		for (int e = 0; e < in_stars / 2; e++)
		{
			cout << "*";
		}

		w_len = sets[i].size();

		for (int e = 0; e < w_len; e++)
		{
			cout << sets[i][e];
			if (e != w_len - 1)
			{
				cout << " ";
			}
		}

		for (int e = 0; e < in_stars / 2; e++)
		{
			cout << "*";
		}

		if (in_stars % 2 != 0)
		{
			cout << "*";
		}
		cout << "\n";
	}

	for (int t = 0; t < 2; t++)
	{
		for (int i = 0; i < columns; i++)
		{
			cout << "*";
		}
		cout << "\n";
	}
}

int main()
{
	cout << "Enter your string:";
	string input_phrase = "";
	getline(cin, input_phrase, '\n');

	vector<vector<string>> set = get_ordered_string(input_phrase);

	printer(set);

	return 0;
}