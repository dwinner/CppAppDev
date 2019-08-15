#ifndef PARSER_H

#define PARSER_H

#define DELIMETER		1
#define VARIABLE		2
#define NUMBER			3

/**
 *	Содержит анализируемое выражение
 */
extern char* prog;
char token[80];
char token_type;

/**
 * \brief Точка входа анализатора
 * \param answer
 */
void start_evaluation(double* answer);

/**
 * \brief Сложение или вычитание 2-х слагаемых
 * \param answer
 */
void eval_add_or_subtract(double* answer);

/**
 * \brief Умножение или деление 2-х множителей
 * \param answer
 */
void eval_multiply_or_divide(double* answer);

/**
 * \brief Возведение в степень
 * \param answer
 */
void eval_power(double* answer);

/**
 * \brief Вычисление унарных операторов + и -
 * \param answer
 */
void eval_unary_plus_minus(double* answer);

/**
 * \brief Вычисление выражения в скобках
 * \param answer
 */
void eval_brackets(double* answer);

/**
 * \brief Получение значения числа
 * \param answer
 */
void atom(double* answer);

/**
 * \brief Возврат очередной лексемы
 */
void get_token();

/**
 * \brief Возврат лексемы в выходной поток
 */
void put_back();

/**
 * \brief Отображение сообщения об ошибке
 * \param error Код ошибки
 */
void set_error(int error);

/**
 * \brief Возвращает значение true, если c является разделителем
 * \param c Символ
 * \return 1, если c разделитель, 0 в противном случае
 */
int is_delim(char c);

#endif // PARSER_H
