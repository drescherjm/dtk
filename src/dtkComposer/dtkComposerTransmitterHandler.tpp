/* dtkComposerTransmitterHandler.tpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 15:29:10 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Mar 21 22:43:47 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 53
 */

/* Change Log:
 * 
 */

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler implementation
// /////////////////////////////////////////////////////////////////

template <typename T, bool U> 
T *dtkComposerTransmitterHandler<T*, U>::copyData(const QVariant& source, QVariant& target, bool enable_copy)
{
    T *data = source.value<T*>();

    if (!data || !enable_copy)
        return data;

    T *copy = target.value<T*>();
    if (!copy) {
	copy = new T(*data)
	target.setValue(copy);
    } else {
	*copy = *data;
    }

    return copy;
}

template <typename T, bool U> 
T *dtkComposerTransmitterHandler<T*, true>::copyData(const QVariant& source, QVariant& target, bool enable_copy)
{
    T *data = source.value<T*>();

    if (!data || !enable_copy)
        return data;

    T *copy = target.value<T*>();;
    if (!copy) {
	copy = data->clone();
	target.setValue(copy);
    } else {
	*copy = *data;
    }

    return copy;
}
