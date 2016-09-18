#include <Grid/Grid.hpp>

namespace container {

template < SizeType Dimension >
SizeType to_position(const Index<Dimension> &index, const Index<Dimension> &range) {
    SizeType pos = static_cast<SizeType>(0);
    SizeType dimProd = static_cast<SizeType>(1);
    for(SizeType D = Dimension; D > static_cast<SizeType>(0); --D) {
        constexpr SizeType d = D - static_cast<SizeType>(1);
        pos += index[d] * dimProd;
        dimProd *= range[d];
    }
    return pos;
}

template < SizeType Dimension >
SizeType to_index(const SizeType position, const Index<Dimension> &range) {
    Index<Dimension> result(static_cast<SizeType>(0));
    SizeType i = position;
    for(SizeType D = Dimension; D > static_cast<SizeType>(0); --D) {
        constexpr SizeType d = D - static_cast<SizeType>(1);
        result[d] = i % range[d];
        i = i / range[d];
    }
    return result;
}



#ifdef GRID_TEMPLATE
#undef GRID_TEMPLATE
#endif
#ifdef GRID_DOMAIN
#undef GRID_DOMAIN
#endif
#define GRID_TEMPLATE template < typename T, SizeType Dimension, class Allocator, SizeType ... Args >
#define GRID_DOMAIN Grid< T, Dimension, Allocator, Args... >



    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTORS
    ////////////////////////////////////////////////////////////////////////

     template < typename T, SizeType Dimension, class Allocator, SizeType ... Args >
    inline GRID_DOMAIN::Grid() :
        DopeVector< T, Dimension, Args...>(nullptr, 0, IndexD::Zero()) {
        this->_array = this->_data.data();
    }

    GRID_TEMPLATE
    inline GRID_DOMAIN::Grid(const IndexD &size, const T & default_value) :
        DopeVector< T, Dimension, Args...>(nullptr, 0, size) {
        this->_data.resize(this->size(), default_value);
        this->_array = this->_data.data();
    }

    GRID_TEMPLATE
    inline GRID_DOMAIN::Grid(const SizeType size, const T & default_value) :
        DopeVector< T, Dimension, Args...>(nullptr, 0, IndexD::Constant(size)) {
        this->_data.resize(this->size(), default_value);
        this->_array = this->_data.data();
    }

    ////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////////////////
    // DESTRUCTOR
    ////////////////////////////////////////////////////////////////////////

    GRID_TEMPLATE
    inline GRID_DOMAIN::~Grid() {}

    ////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////
    // DATA
    ////////////////////////////////////////////////////////////////////////

    GRID_TEMPLATE
    inline const T * GRID_DOMAIN::data() const {
        return this->_data.data();
    }

    GRID_TEMPLATE
    inline T * GRID_DOMAIN::data() {
        return this->_data.data();
    }

    ////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////////////////
    // ITERATORS
    ////////////////////////////////////////////////////////////////////////

    GRID_TEMPLATE
    inline typename GRID_DOMAIN::iterator GRID_DOMAIN::begin() {
        return GRID_DOMAIN::iterator( this->data(), this->_size, 0 );
    }

    GRID_TEMPLATE
    inline typename GRID_DOMAIN::iterator GRID_DOMAIN::end() {
        return GRID_DOMAIN::iterator( this->data(), this->_size, this->size() );
    }

    GRID_TEMPLATE
    inline typename GRID_DOMAIN::const_iterator GRID_DOMAIN::cbegin() const {
        return GRID_DOMAIN::const_iterator( this->data(), this->_size, 0 );
    }

    GRID_TEMPLATE
    inline typename GRID_DOMAIN::const_iterator GRID_DOMAIN::cend() const {
        return GRID_DOMAIN::const_iterator( this->data(), this->_size, this->size() );
    }

    ////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////////////////
    // CONVERSIONS
    ////////////////////////////////////////////////////////////////////////

    GRID_TEMPLATE
    inline typename GRID_DOMAIN::iterator GRID_DOMAIN::to_iterator(const SizeType i) const {
        return (begin() + i);
    }

    GRID_TEMPLATE
    inline typename GRID_DOMAIN::iterator GRID_DOMAIN::to_iterator(const IndexD& i) const {
        return (begin() + position(i));
    }

    GRID_TEMPLATE
    inline typename GRID_DOMAIN::const_iterator GRID_DOMAIN::to_const_iterator(const SizeType i) const {
        return (cbegin() + i);
    }

    GRID_TEMPLATE
    inline typename GRID_DOMAIN::const_iterator GRID_DOMAIN::to_const_iterator(const IndexD& i) const {
        return (cbegin() + position(i));
    }

    GRID_TEMPLATE
    inline const typename GRID_DOMAIN::Data& GRID_DOMAIN::to_stdvector() const {
        return this->_data;
    }

    GRID_TEMPLATE
    inline typename GRID_DOMAIN::Data& GRID_DOMAIN::to_stdvector() {
        return this->_data;
    }

    GRID_TEMPLATE
    inline GRID_DOMAIN::operator Data() const {
        return this->_data;
    }

    ////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////////////////
    // INFORMATION
    ////////////////////////////////////////////////////////////////////////

    GRID_TEMPLATE
    inline bool GRID_DOMAIN::empty() const {
        return this->_data.empty();
    }

    GRID_TEMPLATE
    inline bool GRID_DOMAIN::operator==(const Grid &o) const {
        return (this->_size == o._size) && (this->_data == o._data);
    }

    ////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////////////////
    // RESET
    ////////////////////////////////////////////////////////////////////////

    GRID_TEMPLATE
    inline void GRID_DOMAIN::clear() {
        this->_data.clear();
        this->_array = this->_data.data();
    }

    GRID_TEMPLATE
    inline void GRID_DOMAIN::reset(const T & default_value) {
        this->_data.clear();
        this->_data.resize(this->size(), default_value);
        this->_array = this->_data.data();
    }

    ////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////////////////
    // ASSIGNMENTS
    ////////////////////////////////////////////////////////////////////////

    GRID_TEMPLATE
    inline void GRID_DOMAIN::swap(Grid &o) {
        DopeVector< T, Dimension, Args ... >::swap(o);
        this->_data.swap(o._data);
    }

    ////////////////////////////////////////////////////////////////////////



#undef GRID_TEMPLATE
#undef GRID_DOMAIN

}
