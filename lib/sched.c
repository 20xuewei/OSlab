#include <env.h>
#include <pmap.h>
#include <printf.h>

/* Overview:
 *  Implement simple round-robin scheduling.
 *
 *
 * Hints:
 *  1. The variable which is for counting should be defined as 'static'.
 *  2. Use variable 'env_sched_list', which is a pointer array.
 *  3. CANNOT use `return` statement!
 */
/*** exercise 3.14 ***/
void sched_yield(void)
{
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current env_sched_list index
    struct Env *e = curenv, *var;
    /*  hint:
     *  1. if (count==0), insert `e` into `env_sched_list[1-point]`
     *     using LIST_REMOVE and LIST_INSERT_TAIL.
     *  2. if (env_sched_list[point] is empty), point = 1 - point;
     *     then search through `env_sched_list[point]` for a runnable env `e`,
     *     and set count = e->env_pri
     *  3. count--
     *  4. env_run()
     *
     *  functions or macros below may be used (not all):
     *  LIST_INSERT_TAIL, LIST_REMOVE, LIST_FIRST, LIST_EMPTY
     */
/*
    printf("start yield:\n");
    if (curenv!=NULL) printf("curenv id: %d count: %d\n", curenv->env_id, count);
    else printf("curenv: NULL\n");
    if (LIST_EMPTY(&env_sched_list[point])) printf("%d: NULL\n", point);
    else {
	struct Env *var;
	LIST_FOREACH(var, (&env_sched_list[point]), env_sched_link) {
		printf("%d: status:%d id:%d pri:%d\n", point, var->env_status, var->env_id, var->env_pri);
	}
    }
    if (LIST_EMPTY(&env_sched_list[1-point])) printf("%d: NULL\n", 1-point);
    else {
	struct Env *var;
	LIST_FOREACH(var, (&env_sched_list[1-point]), env_sched_link) {
		printf("%d: status:%d id:%d pri:%d\n", 1 - point, var->env_status, var->env_id, var->env_pri);
	}
    }

*/
    while(e == NULL || count <= 0 || (e && e -> env_status != ENV_RUNNABLE)) {
        count = 0;
        if(e != NULL) {
            LIST_REMOVE(e, env_sched_link);
            if(e -> env_status != ENV_FREE) LIST_INSERT_TAIL(&env_sched_list[point^1], e, env_sched_link);
        }
        if(LIST_EMPTY(&env_sched_list[point])) point ^= 1;
        if(LIST_EMPTY(&env_sched_list[point])) continue;
        e = LIST_FIRST(&env_sched_list[point]);
        if(e != NULL) count = e -> env_pri;
    } 
	
    if (count>0) count--;
    env_run(e);
}
