/**
 * @brief      Wraps two pointers.
 *
 * @tparam     T1    Type of first.
 * @tparam     T2    Type of second.
 */
template<class T1, class T2>
class Tuple
{
public:
	/**
	 * Allows access to first parameter.
	 */
	T1* first;

	/**
	 * Allows access to second parameter.
	 */
	T2* second;

	/**
	 * @brief      Constructor.
	 */
	Tuple()
	{

	}

	/**
	 * @brief      Constructor.
	 *
	 * @param      first   The first object.
	 * @param      second  The second object.
	 */
	Tuple(T1* first, T2* second)
	{
		this.first = first;
		this.second = second;
	}
};