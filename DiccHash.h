#ifndef _DICCHASH_H_
#define _DICCHASH_H_

#include <string>
#include <iostream>
#include <set>
#include <list>
#include <vector>

using namespace std;

/* Tamaño inicial de la tabla */
#ifndef TAM_INICIAL
#define TAM_INICIAL 100
#endif

/* Factor de carga a partir del cual se redimensiona la tabla */
#ifndef UMBRAL_FC
#define UMBRAL_FC         0.75
#endif

template<class V>
class DiccHash {
public:

    /* Constructor sin parámetros de la clase */
    DiccHash();

    /* Destructor */
    ~DiccHash();

    /* Devuelve true si la clave está definida en el diccionario.
     * - clav : clave a buscar
     */
    bool definido(const string& clav) const;

   /* Agrega una clave y su significado al Diccionario.
    * Si la clave a agregar ya se encuentra definida,
    * redefine su significado.
    * - clav : clave a agregar
    * - sig  : significado de la clave a agregar
    *
    * Nota de implementación:
    *
    * Si el factor de carga supera el valor de UMBRAL_FC, se debe
    * redimensionar la tabla al doble de tamaño.
    *
    * Pasos a seguir para redimensionar la tabla:
    * - Crear una tabla del doble de tamaño de la original.
    * - Insertar todas las claves de la tabla original en la tabla nueva.
    * - Liberar la memoria reservada para la tabla original.
    */
    void definir(const string& clav, const V& sig);

    /* Busca en el diccionario el significado de la clave clav.
     * - clav : clave a buscar
     * Devuelve el significado de clav.
     */
    V& significado(const string& clav);

    /* Borra la clave del diccionario
     * - clav : clave a borrar
     *
     * Precondición: clav está definida en el diccionario */
    void borrar(const string& clav) ;

    /* Devuelve la cantidad de claves definidas en el diccionario. */
    unsigned int cantClaves() const;

    /* Devuelve el conjunto de claves del diccionario. */
    set<string> claves() const;

    /* SÓLO PARA TESTING
     *
     * Devuelve el factor de carga de la tabla de hash.
     * Factor de carga : cantidad de claves definidas / tamaño de la tabla.
     */
    float factorCarga() const;

    /* SÓLO PARA TESTING
     * Devuelve la cantidad de colisiones que tiene el diccionario.
     *
     * Observación: si en una celda de la tabla conviven n elementos,
     * hay n * (n - 1) / 2 colisiones en esa celda.
     */
    unsigned int colisiones() const;

private:

    struct Asociacion {
            string clave;
            V valor;
            Asociacion (const string clav ,const V& val) : clave(clav) , valor(val){};
     };

    set<string> llaves;
    vector<list<Asociacion> > _tabla;
    unsigned int _tam;
    unsigned int _cant_claves;

   /* Función de hash.
    * Recordar usar "hash = hash % _tam".
    * (El operador "%" calcula el resto en la división o "módulo").
    * Devuelve la posición de la tabla asociada a la clave dada.
    */
    unsigned int fn_hash(const string& str) const;

      void redimensionamiento( vector<list<Asociacion>> dh){
        vector<list<Asociacion>> dh2 (this->_tam * 2);
        for (list<Asociacion> l : dh ){
            dh2.push_back(l);
            }
        dh.swap(dh2);
        _tam = _tam*2;
    };
};

#include "DiccHash.hpp"

#endif /*_DICCHASH_H_*/

