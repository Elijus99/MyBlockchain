# MyBlockchain

Blockchain C++ implementation

## Task

Sukurkite "centralizuotą" blokų grandinę (blockchain'ą) ir susimuliuokite blokų grandinės veikimą kuo natūralesnėmis sąlygomis. Norint tai pasiekti, preliminari veiksmų seka (nebūtinai eilės tvarka, tokia kokia čia nurodyta) galėtų būti tokia:

1. Sugeneruoti ~1000 tinklo vartotojų (aka user'ių), kurie turėtų bent tris atributus: `vardą`, viešąjį _hash_ raktą (`public_key`) ir tam tikros valiutos (galite pasivadinti savo vardu :smile: ) atsitiktinį balansą, pvz. nuo 100 iki 1000000 vienetų.
2. Sugeneruoti tam tikrą skaičių, pvz., transkacijų _pool_'ą sudarytą iš 10000 atsitiktinių transakcijų (jų struktūrą kol kas yra neformalizuota) tarp visų vartotojų, kurių metu jie vienas kitam atlikinėtų tam tikro atsitiktinio dydžio pinigų pervedimus.
3. Iš šių transakcijų atsitiktinai pasirinkti 100-ą (tarsime, kad blokas talpins apie 100 transakcijų) ir jas priskirti naujam sugeneruotam blokui (kurį kitame žingsnyje dar reikės "iškąsti"), kurio struktūra nurodyta paveiksle aukščiau.
4. Realizuoti naujų blokų kasimo (angl. *mining*) Proof-of-Work (PoW) procesą, kurio tikslas yra surasti naujam blokui hash'ą, tenkinantį `Difficulty Targer` reikalavimą, t.y., hash'o pradžioje esančių nulių skaičių.
5. Suradus tokį naujo bloko hash'ą, bloką pridėti prie grandinės. Kartoti 3-5 žingsnius tol, kol yra laisvų transakcijų.

## How to install and run (UNIX terminal)

- `git clone https://github.com/Elijus99/MyBlockchain.git`
- `cd MyBlockchain`
- `make`
- `make run`

### Blockchain block structure

- Nonce
- Difficulty target
- Version
- Merkle Root Hash
- Timestamp
- Previous Block Hash


## Changelog

### [v0.1](https://github.com/Elijus99/MyBlockchain/releases/tag/v0.1) - (2019-10-23)

- First program version

### [v0.1.5](https://github.com/Elijus99/MyBlockchain/releases/tag/v0.1.5) - (2019-12-12)

Added transactions validation:
1. Balance checking: Checks if sender has enough coins to do the transaction.
2. Transaction hash checking: checks if transaction was not forged while travelling to the transactions pool.

### [v0.2 && v0.3](https://github.com/Elijus99/MyBlockchain/releases/tag/v0.3)

Improved block mining process:
1. Five potential blocks are created.
2. Each potential block takes turn in random order with 100000 attempts to find a hash value that would meet the `Difficulty target` requirement.
3. If none of the 5 blocks meet the requirement, attempts per turn value gets increased by 100000. Process repeats until the fitting hash value is found.
