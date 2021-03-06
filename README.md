Trains Protocol : a uniform and totally-ordered broadcast protocol
==================================================================

Trains protocol is a uniform and totally-ordered broadcast protocol [Défago et al., 2004].

It is designed to be a throughput-efficient protocol, especially for short messages (100 bytes or lower) [Simatic, 2012].


Purpose of this fork
--------------------
This project is forked from http://github.com/simatic/TrainsProtocol.
It aims to simplify stateMachine.c

Compilation of Trains protocol middleware
-----------------------------------------
make (with no target) generates the library, the unit and integration tests, 

make doc              generates the doxygen documentation.

There is no installation target.

Generating an application using Trains protocol
-----------------------------------------------
tests/integration/basic contains a basic integration test which shows the APIs which can be used.

To compile, you should add "-Iinclude" (where "include" is the path to "include" directory of this TrainsProtocol GIT project) to your compilation instruction

To link, you should add "-Lsrc -ltrains -pthread" (where "src" is the path to "src" directory of this TrainsProtocol GIT project) to your link instruction

Running an application using Trains protocol
-----------------------------------------------
In the directory where you will launch your application, create a file called addr_file which describes the participants processes. Each line should follow the rank:hostname:port rule syntax.
- rank : the rank the protocol participant process will have in your application (between 0 and 15)
- hostname : the name of a host (may be localhost) on which you will run your application
- port : the port which shall be used by your application

See tests/integration/basic/addr_file for an example

export TRAINS_PORT=port to be used by application

Known issues
------------
See "Known issues" section in ./doc/RELEASE-NOTES.txt

Bibliography
------------
[Défago et al., 2004] Défago, X., Schiper, A. et Urbán, P. (2004). Total order broadcast and multicast algorithms : Taxonomy and survey. ACM Comput. Surv., 36:372?421.

[Simatic, 2012] M. Simatic. Communication et partage de données dans les systèmes répartis (Data communication and data sharing in distributed system, in French). PhD thesis, École Doctorale ÉDITE, October 2012 (available at http://www-public.it-sudparis.eu/~simatic/Recherche/Publications/theseSimatic.pdf).
