/**
  @file set.hpp

  @brief File header della classe Set templata

  File di dichiarazioni/definizioni della classe set templata
*/

#ifndef SET_HPP
#define SET_HPP

#include <algorithm> 
#include <ostream> 
#include <iterator>
#include <cstddef>
#include <cassert>
#include <fstream>
#include <string>


/**
  @brief classe set ordinata

  La classe implementa un generico set di oggetti T.
*/
template <typename T, typename Equals>
class set
{
    public:
    // Traits
    typedef unsigned int size_type;
    typedef T value_type;

    private:
    value_type *_array;  //puntatore all'array
    size_type _size;  //dimensione dell'array
    size_type _limit;  //prima posizione vuota dell'array

    Equals _eql;  //funtore per l'uguaglianza tra dati T

    /**
        @brief Ritorna la posizione di un value all'interno di un set

        @param value il valore da ricercare

        @return -1, se il value non e' presente, la posizione altrimenti
    */ 
    int search(const value_type &value) const
    {
        if(_limit == 0)
            return -1;
        else
            for(size_type i=0; i<_limit; i++)
                if(_eql(_array[i], value))
                    return i;

        return -1;
    }

    public:

    /**
        @brief Metodo per rimuovere gli elementi di un set
    */
    void empty()
    {
        delete[] _array;
        _array = nullptr;
        _size = 0;
        _limit = 0;
    }

    /**
        @brief Costruttore di default.

        @post _array == nullptr
        @post _size == 0
        @post _limit == 0
    */
    set() : _array(nullptr), _size(0), _limit(0) {}

    /**
        @brief Costruttore secondario.

        @post _array == nullptr
        @post _size == n
        @post _limit == 0
    */
    set(size_type size) : _limit(0)
    {
        assert(size >= 0);
        _array = new value_type[size];
        _size = size;
    }

    /**
        @brief Copy constructor

        @param other set da copiare

        @throw possibile eccezzione di allocazione
    */
    set(const set &other) : _array(nullptr), _size(0), _limit(0)
    {
        try
        {
            _array = new value_type[other._size];

            _size = other._size;
            _limit = other._limit;

            for(size_type i=0; i<_limit; i++)
            {
                _array[i] = other._array[i];
            }
        }
        catch(...)
        {
            empty();
            throw;
        }
    }

    /**
        @brief Operatore per lo swap

        @param other set da swappare
    */
    void swap(set &other)
    {
        std::swap(this->_array, other._array);
        std::swap(this->_size, other._size);
        std::swap(this->_limit, other._limit);
        std::swap(this->_eql, other._eql);
    }

    /**
        @brief Operatore di assegnamento

        @param other set da copiare

        @return reference a this.set
    */
    set &operator=(const set &other)
    {
        if (&other != this)
        {
            set tmp(other);
            this->swap(tmp); 
        }
        return *this;
    }

    /**
        @brief Distruttore 

        @post _head == nullptr
    */
    ~set()
    {
        empty();
    }

    /**
        @brief Costruttore che crea una set partendo da una sequenza
        di dati definiti da una coppia di iteratori su tipi Q

        @param begin iteratore di inizio sequenza
        @param end iteratore di fine sequenza

        @throw possibile eccezzione di allocazione
    */
    template <typename Q>
    set(const Q begin, const Q end) : _array(nullptr), _size(0), _limit(0)
    {
        try
        {
            Q tmp = begin;
            while(tmp!=end)
            {
                this->add(static_cast<T>(*tmp));
                tmp++;
            } 
        }
        catch(...)
        {
            empty();
            throw;
        }
    }  

    /**
        @brief Controlla se un certo valore e' presente nel set

        @param value il valore da controllare

        @return true se il valore esiste nel set, false altrimenti
    */
    bool contains(const value_type &value) const
    {
        if(_limit == 0)
            return false;
        else
            for(size_type i=0; i<_limit; i++)
                if(_eql(value, _array[i]))
                    return true;

        return false;
    }

    /**
        @brief Aggiunge un elemento al set

        @param value il valore da inserire

        @return true se il valore e' stato aggiunto con successo, false altrimenti

        @throw possibile eccezzione di allocazione
    */
    bool add(const value_type &value)
    {
        if(contains(value))
            return false;
        else
        {
            if(_limit >= _size)  //se lo spazio e' esaurito
            {
                size_type _new_size = _size * 2;

                if(_new_size == 0)
                    _new_size = 1;
                try 
                {
                    value_type *_new_array = new value_type[_new_size];

                    for(size_type i = 0; i<_limit; i++)
                        _new_array[i] = _array[i]; 

                    _size = _new_size;
                    delete[] _array;
                    _array = _new_array;
                    _new_array = nullptr; 
                }
                catch(...)
                {
                    throw;
                }          
            }
            _array[_limit] = value;
            _limit++;
            return true; 
        }
    }

    /**
        @brief Rimuove un elemento al set

        @param value il valore da rimuovere

        @return true se il valore e' stato rimosso con successo, false altrimenti

        @throw possibile eccezzione di allocazione
    */
    bool remove(const value_type &value)
    {
        int result = search(value);
        if(result != -1)
        {
            _array[result] = _array[_limit-1];
            _limit--;

            if(_limit <= _size/2)
            {
                size_type _new_size = _size - (_size/4);  //prendo i 3/4 della dimesnione
                try
                {
                    value_type *_new_array = new value_type[_new_size];

                    for(size_type i = 0; i<_limit; i++)
                        _new_array[i] = _array[i]; 

                    _size = _new_size;
                    delete[] _array;
                    _array = _new_array;
                    _new_array = nullptr; 
                }
                catch(...)
                {
                    throw;
                }
            }

            return true;

        }
        else
            return false;
        return false;
    }

    /**
        @brief Operatore getter di una cella dell'array

        @param index della cella da leggere

        @return reference al'intero da leggere
        
        @pre index < _limit
    */
    const value_type &operator[](const size_type index) const
    {
        assert(index >= 0);
        assert(index < _limit);
        return _array[index];
    }

    /**
        @brief Operatore di uguaglianza tra due set

        @param other set da paragonare

        @return true se i set sono uguali, false altrimenti
    */
    bool operator==(const set &other) const
    {
        if(_limit == other._limit)
        {
            for(size_type i=0; i<other._limit; i++)
                if(!contains(other[i]))
                    return false;
        }
        else
            return false;

        return true;
    }

    /**
        @brief Operatore di disuguaglianza tra due set

        @param other set da paragonare

        @return false se i set sono uguali, true altrimenti
    */
    bool operator!=(const set &other) const
    {
        return !(this==other);
    }

    /**
        @brief Funzione GLOBALE che implementa l'operatore di stream.
        La funzione e' templata sull set ed e' messa
        friend perche' accediamo ai dati privati di set.

        @param os stream di output
        @param ol set da spedire sullo stream

        @return lo stream di output
    */
    friend std::ostream& operator<<(std::ostream &os, const set &st)
    {
        os<<st._limit<<" ";
        
        for(int i=0; i<st._limit; i++)
        {
            os<<" ("<<st[i]<<")";
        }

        return os;
    }
    
    class const_iterator
    {
        public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T                         value_type;
        typedef ptrdiff_t                 difference_type;
        typedef const T*                  pointer;
        typedef const T&                  reference;

        private:
        const T *ptr;
        friend class set;
        const_iterator(const T *p) : ptr(p) {}

        public:
        const_iterator() : ptr(nullptr) {}
        
        const_iterator(const const_iterator &other) : ptr(other.ptr) {}

        const_iterator &operator=(const const_iterator &other)
        {
            ptr = other.ptr;
            return *this;
        }

        ~const_iterator() {}

        reference operator*() const
        {
            return *ptr;
        }

        pointer operator->() const
        {
            return ptr;
        }
        
        const_iterator operator++(int) 
        {
            const_iterator tmp(*this);
            ptr++;
            return tmp;
        }

        const_iterator& operator++()
        {
            ++ptr;
            return *this;
        }

        bool operator==(const const_iterator &other) const
        {
            return ptr==other.ptr;
        }
        
        bool operator!=(const const_iterator &other) const
        {
            return ptr!=other.ptr;
        }   
    };
        
    const_iterator begin() const
    {
        return const_iterator(_array);
    }

    const_iterator end() const
    {
        return const_iterator(_array + _limit);
    }
};


/**
    @brief Filtra un set in base ad un predicato P

    Dati un set generico S su tipi T e un predicato
    booleano generico P, ritorna un nuovo set di tipi T ottenuto
    prendendo da S tutti gli elementi che soddisfano P

    @param st set di tipi T da filtrare
    @param predicato funzione per filtrare st

    @return set contentente i valori di st che soddisfano predicato

    @throw possibile eccezzione di allocazione
*/
template<typename T, typename Equals,typename P>
set<T, Equals> filter_out(const set<T, Equals> &st, P predicato)
{
    set<T, Equals> result;
    typename set<T, Equals>::const_iterator ib, ie;

    try
    {
       for(ib=st.begin(), ie=st.end(); ib!=ie; ib++)
        if(predicato(*ib))
            result.add(*ib); 
    }
    catch(...)
    {
        throw;
    }
    return result;
}


/**
    @brief dati in input due Set su tipi T, ritorna un Set di tipi T 
    che contiene gli elementi di entrambi i set

    @param set1 primo set
    @param set2 secondo set

    @return set contentente l'unione tra set1 e set2
*/
template<typename T, typename Equals>
set<T, Equals> operator+(const set<T, Equals> &set1, const set<T, Equals> &set2)
{
    set<T, Equals> result;
    result = set1;
    typename set<T, Equals>::const_iterator ib, ie;

    for(ib=set2.begin(), ie=set2.end(); ib!=ie; ib++)
        result.add(*ib);

    return result;
}


/**
    @brief dati in input due Set su tipi T, ritorna un Set di tipi T 
    che contiene gli elementi comuni a entrambi i set

    @param set1 primo set
    @param set2 secondo set

    @return set contentente l'intersezione tra set1 e set2
*/
template<typename T, typename Equals>
set<T, Equals> operator-(const set<T, Equals> &set1, const  set<T, Equals> &set2)
{
    set<T, Equals> result;
    typename set<T, Equals>::const_iterator ib, ie;

    for(ib=set2.begin(), ie=set2.end(); ib!=ie; ib++)
        if(set1.contains(*ib))
            result.add(*ib);

    return result;
}

/**
    @brief stampa il set su un file

    @param st set da stampare
    @param filename nome del file sul quale si vuole scrivere

    @throw possibile eccezzione mancata scrittura sul file
*/
template<typename Equals>
void save(const set<std::string, Equals> &st, const std::string &filename)
{
    std::ofstream out_file;
    try
    {
        out_file.open(filename);
        out_file << st;
        out_file.close();
    }
    catch(...)
    {
        if(out_file.is_open())
            out_file.close();
        throw;
    }
}

#endif