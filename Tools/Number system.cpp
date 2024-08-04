string Number_system(int number, int from_base, int to_base, bool upper = false) {
    string digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    if (to_base > digits.length()) {
        return "";
    }
    else {
        string result = "";
        while (number > 0) {
            result = digits[number % to_base] + result;
            number /= to_base;
        }
        if (upper) {
            for (char& c : result) {
                c = toupper(c);
            }
        }
        return result;
    }
}
