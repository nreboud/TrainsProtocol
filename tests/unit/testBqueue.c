/**
 Trains Protocol: Middleware for Uniform and Totally Ordered Broadcasts
 Copyright: Copyright (C) 2010-2012
 Contact: michel.simatic@telecom-sudparis.eu

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3 of the License, or any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 USA

 Developer(s): Michel Simatic, Arthur Foltz, Damien Graux, Nicolas Hascoet, Nathan Reboud
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <error.h>

#include "bqueue.h"
#include "list.h"

trBqueue *q;

char *a = "A";
char *b = "B";
char *c = "C";

void *functionThread1(void *null) {
  bqueueEnqueue(q, a);
  bqueueEnqueue(q, b);
  bqueueEnqueue(q, c);
  return NULL;
}

void compare(void *s, char *target){
  if ( (s == NULL) || (s != target)){
    printf("... KO (s is \"%s\" instead of \"%s\")\n", (char *)s, target);
    exit(EXIT_FAILURE);
  }
}

int main() {
  int rc;
  pthread_t thread;
  trList *l;

  q = newBqueue();

  printf("testing bqueue...");
  fflush(stdout); // Pour avoir l'affichage ci-dessus, même si on se bloque pendant le test

  bqueueEnqueue(q, a);
  bqueueEnqueue(q, b);
  bqueueEnqueue(q, c);

  compare(bqueueDequeue(q), a);
  compare(bqueueDequeue(q), b);
  compare(bqueueDequeue(q), c);

  rc = pthread_create(&thread, NULL, &functionThread1, NULL);
  if (rc < 0)
    error_at_line(EXIT_FAILURE, rc, __FILE__, __LINE__, "pthread_create");

  compare(bqueueDequeue(q), a);
  compare(bqueueDequeue(q), b);
  compare(bqueueDequeue(q), c);

  l = newList();
  bqueueExtend(q,l);
  listAppend(l,a);
  listAppend(l,b);
  listAppend(l,c);
  bqueueExtend(q,l);
  cleanList(l);
  listAppend(l,a);
  listAppend(l,b);
  listAppend(l,c);
  bqueueExtend(q,l);

  compare(bqueueDequeue(q), a);
  compare(bqueueDequeue(q), b);
  compare(bqueueDequeue(q), c);
  compare(bqueueDequeue(q), a);
  compare(bqueueDequeue(q), b);
  compare(bqueueDequeue(q), c);
  
  // free memory 
  rc = pthread_join(thread, NULL);
  if(rc)
    error_at_line(EXIT_FAILURE, rc, __FILE__, __LINE__, "pthread_join");

  freeBqueue(q);

  printf("OK\n");

  return EXIT_SUCCESS;
}

  
