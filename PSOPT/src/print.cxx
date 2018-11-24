/*********************************************************************************************

This file is part of the PSOPT library, a software tool for computational optimal control

Copyright (C) 2009-2015 Victor M. Becerra

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA,
or visit http://www.gnu.org/licenses/

Author:    Professor Victor M. Becerra
           University of Reading
           School of Systems Engineering
           P.O. Box 225, Reading RG6 6AY
           United Kingdom
           e-mail: vmbecerra99@gmail.com

**********************************************************************************************/

#include "psopt.h"

void psopt_print(Workspace* workspace, const char* msg)
{
    if (workspace->algorithm->print_level) {
         fprintf(stderr,"%s", msg);
    }
    sprintf(workspace->text,"%s"," ");
}


void print_iterations_summary(Prob& problem,Alg& algorithm,Sol& solution, Workspace* workspace)
{

	int nphases = problem.nphases;
	int iphase;
	FILE* outfile  = workspace->psopt_solution_summary_file;
        FILE* outfile2 = workspace->mesh_statistics;
	int jj;

	int sum_n_jacobian_evals   = 0;
	int sum_n_hessian_evals    = 0;
	int sum_n_obj_evals        = 0;
	int sum_n_con_evals        = 0;
	int sum_n_ode_rhs_evals    = 0;
	double sum_CPU_time        = 0.0;


        fprintf(outfile,"\n\n*****************************************************************************************************************");
        fprintf(outfile,"\n************************************* Mesh Refinement Statistics ************************************************");
	fprintf(outfile,"\n*****************************************************************************************************************");

	fprintf(outfile,"\n\nIter\tMethod\tNodes\tNV\tNC\tOEval\tCEval\tJEval\tHEval\tODE RHS\tODE Error\tNLP CPU(sec)");

	for (jj=0;jj< workspace->current_mesh_refinement_iteration;jj++) {

	  fprintf(outfile,"\n%i\t%s\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%e\t%e", jj+1, solution.mesh_stats[jj].method.c_str(), solution.mesh_stats[jj].nnodes, solution.mesh_stats[jj].nvars,
		solution.mesh_stats[jj].ncons, solution.mesh_stats[jj].n_obj_evals, solution.mesh_stats[jj].n_con_evals,
		solution.mesh_stats[jj].n_jacobian_evals, solution.mesh_stats[jj].n_hessian_evals,
		solution.mesh_stats[jj].n_ode_rhs_evals, solution.mesh_stats[jj].epsilon_max,
		solution.mesh_stats[jj].CPU_time);

		sum_n_jacobian_evals   += solution.mesh_stats[jj].n_jacobian_evals;
	        sum_n_hessian_evals    += solution.mesh_stats[jj].n_hessian_evals;
	        sum_n_obj_evals        += solution.mesh_stats[jj].n_obj_evals;
		sum_n_con_evals        += solution.mesh_stats[jj].n_con_evals;
	        sum_n_ode_rhs_evals    += solution.mesh_stats[jj].n_ode_rhs_evals;
	        sum_CPU_time           += solution.mesh_stats[jj].CPU_time;
	}

        fprintf(outfile,"\n__________________________________________________________________________________________________________________\n\n");

	double diff_CPU_time = solution.cpu_time - sum_CPU_time;

	        fprintf(outfile,"\nAdditional CPU time (sec)\t\t\t\t\t\t\t\t\t%e",
		diff_CPU_time);

		fprintf(outfile,"\nTotals\t-\t-\t-\t-\t%i\t%i\t%i\t%i\t%i\t-\t\t%e",
		sum_n_obj_evals, sum_n_con_evals,
		sum_n_jacobian_evals, sum_n_hessian_evals,
		sum_n_ode_rhs_evals,
		solution.cpu_time);

        fprintf(outfile,"\n__________________________________________________________________________________________________________________\n\n");


	fclose(outfile);


	fprintf(outfile2,"\n\n*****************************************************************************************************************");
        fprintf(outfile2,"\n************************************* Mesh Refinement Statistics ************************************************");
	fprintf(outfile2,"\n*****************************************************************************************************************");

	fprintf(outfile2,"\n\nIter\tMethod\tNodes\tNV\tNC\tOEval\tCEval\tJEval\tHEval\tODE RHS\tODE Error\tNLP CPU(sec)");

	for (jj=0;jj< workspace->current_mesh_refinement_iteration;jj++) {

	  fprintf(outfile2,"\n%i\t%s\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%e\t%e", jj+1, solution.mesh_stats[jj].method.c_str(), solution.mesh_stats[jj].nnodes, solution.mesh_stats[jj].nvars,
		solution.mesh_stats[jj].ncons, solution.mesh_stats[jj].n_obj_evals, solution.mesh_stats[jj].n_con_evals,
		solution.mesh_stats[jj].n_jacobian_evals, solution.mesh_stats[jj].n_hessian_evals,
		solution.mesh_stats[jj].n_ode_rhs_evals, solution.mesh_stats[jj].epsilon_max,
		solution.mesh_stats[jj].CPU_time);









	}

        fprintf(outfile2,"\n__________________________________________________________________________________________________________________\n\n");


	        fprintf(outfile2,"\nAdditional CPU time (sec)\t\t\t\t\t\t\t\t\t%e",
		diff_CPU_time);

		fprintf(outfile2,"\nTotals\t-\t-\t-\t-\t%i\t%i\t%i\t%i\t%i\t-\t\t%e",
		sum_n_obj_evals, sum_n_con_evals,
		sum_n_jacobian_evals, sum_n_hessian_evals,
		sum_n_ode_rhs_evals,
		solution.cpu_time);

        fprintf(outfile2,"\n__________________________________________________________________________________________________________________\n\n");


	fclose(outfile2);


}


void print_iterations_summary_tex(Prob& problem,Alg& algorithm,Sol& solution, Workspace* workspace)
{

	int nphases = problem.nphases;
	int iphase;
	FILE* outfile = workspace->mesh_statistics_tex;
	int jj;

	string caption, label, table_key;

	int sum_n_jacobian_evals   = 0;
	int sum_n_hessian_evals    = 0;
	int sum_n_obj_evals        = 0;
	int sum_n_con_evals        = 0;
	int sum_n_ode_rhs_evals    = 0;
	double sum_CPU_time        = 0.0;



	if (algorithm.print_level==0) return;

	int dotindex = problem.outfilename.find_first_of(".");

	string msname = "mesh_stats_" + problem.outfilename.substr(0,dotindex);

	caption = "\n\\caption{Mesh refinement statistics: " + problem.name + "}";
	label   = "\n\\label{" + msname + "}";
	table_key     = "\n\\newline \\\\ \\emph{Key}: Iter=iteration number, DM= discretization method, M=number of nodes, NV=number of variables, NC=number of constraints, OE=objective evaluations,  \
	              CE = constraint evaluations, JE = Jacobian evaluations, HE = Hessian evaluations, RHS = ODE right hand side \
		      evaluations, $\\epsilon_{\\max}$ = maximum relative ODE error, CPU$_\\mathrm{a}$ = CPU time in seconds spent by NLP algorithm, \
		      CPU$_\\mathrm{b}$ = additional CPU time in seconds spent by PSOPT";



	fprintf(outfile,"\n\\begin{table}");

	fprintf(outfile,"%s",caption.c_str());

        fprintf(outfile,"%s",label.c_str());

	fprintf(outfile,"%s","\n\\renewcommand{\\tabcolsep}{0.15cm}");

        fprintf(outfile,"\n\\tiny");

        fprintf(outfile,"\n\\begin{tabular}{llllllllllll}");

	fprintf(outfile,"\nIter&DM&M&NV&NC&OE&CE&JE&HE&RHS&$\\epsilon_{\\max}$&CPU$_\\mathrm{a}$ \\\\ \\hline \\\\");

	for (jj=0;jj< workspace->current_mesh_refinement_iteration;jj++) {

	  fprintf(outfile,"\n%i&%s&%i&%i&%i&%i&%i&%i&%i&%i&%.3e&%.3e\\\\", jj+1, solution.mesh_stats[jj].method.c_str(), solution.mesh_stats[jj].nnodes, solution.mesh_stats[jj].nvars,
		solution.mesh_stats[jj].ncons, solution.mesh_stats[jj].n_obj_evals, solution.mesh_stats[jj].n_con_evals,
		solution.mesh_stats[jj].n_jacobian_evals, solution.mesh_stats[jj].n_hessian_evals,
		solution.mesh_stats[jj].n_ode_rhs_evals, solution.mesh_stats[jj].epsilon_max,
		solution.mesh_stats[jj].CPU_time);

		sum_n_jacobian_evals   += solution.mesh_stats[jj].n_jacobian_evals;
	        sum_n_hessian_evals    += solution.mesh_stats[jj].n_hessian_evals;
	        sum_n_obj_evals        += solution.mesh_stats[jj].n_obj_evals;
		sum_n_con_evals        += solution.mesh_stats[jj].n_con_evals;
	        sum_n_ode_rhs_evals    += solution.mesh_stats[jj].n_ode_rhs_evals;
	        sum_CPU_time           += solution.mesh_stats[jj].CPU_time;
	}

	double diff_CPU_time = solution.cpu_time - sum_CPU_time;

        fprintf(outfile,"\n\\hline");
		fprintf(outfile,"\nCPU$_\\mathrm{b}$ &-&-&-&-&-&-&-&-&-&-&%.3e\\\\",
		diff_CPU_time);

		fprintf(outfile,"\n-&-&-&-&-&%i&%i&%i&%i&%i&-&%.3e\\\\",
		sum_n_obj_evals, sum_n_con_evals,
		sum_n_jacobian_evals, sum_n_hessian_evals,
		sum_n_ode_rhs_evals,
		solution.cpu_time);

        fprintf(outfile,"\n\\end{tabular}");

	fprintf(outfile,"%s",table_key.c_str());

        fprintf(outfile,"\n\\normalsize");

        fprintf(outfile,"\n\\end{table}");

	fclose(outfile);

}



void print_psopt_summary(Prob& problem, Alg& algorithm, Sol& solution, Workspace* workspace)
{
    FILE* outfile;
    string auxstr;
    string filename;
    string mesh_stats_file = "mesh_statistics.txt";
    int i;
    DMatrix mv(1);

    if ( !algorithm.print_level ) return;

    if ( problem.outfilename == "" )
       filename = "psopt.txt";
    else
       filename = problem.outfilename;
    outfile = fopen( filename.c_str(), "w");
    fprintf(outfile,"\nPSOPT results summary");
    fprintf(outfile,"\n=====================\n");

    auxstr = "Problem: \t\t\t\t\t" + problem.name ;
    fprintf(outfile,"\n%s", auxstr.c_str());
    fprintf(outfile,"\nCPU time (seconds):\t\t\t\t%e", solution.cpu_time);
    fprintf(outfile,"\nNLP solver used: \t\t\t\t%s", algorithm.nlp_method.c_str());

    if ( algorithm.nlp_method == "IPOPT") {
        if (solution.nlp_return_code  == 0) {
            fprintf(outfile,"\nOptimal (unscaled) cost function value: \t%e", solution.cost);
            for (i=0;i < problem.nphases; i++) {
		mv = mean(tra(solution.relative_errors[i]));
            	fprintf(outfile,"\nPhase %i endpoint cost function value:\t\t%e",i+1, solution.endpoint_cost[i]);
            	fprintf(outfile,"\nPhase %i integrated part of the cost: \t\t%e", i+1, solution.integrated_cost[i]);
            	fprintf(outfile,"\nPhase %i initial time:\t\t\t\t%e",i+1, (solution.nodes[i])(1));
                fprintf(outfile,"\nPhase %i final time:\t\t\t\t%e",i+1, (solution.nodes[i])("end"));
		fprintf(outfile,"\nPhase %i maximum relative local error:\t\t%e", i+1, Max(solution.relative_errors[i]) );

	    }
            auxstr = "The problem solved!";
        }
        else {
           auxstr = "*** The problem FAILED! - see screen output";
           fprintf(outfile,"\nReturned (unscaled) cost function value: \t%e", solution.cost);
            for (i=0;i < problem.nphases; i++) {
		mv = mean(tra(solution.relative_errors[i]));
            	fprintf(outfile,"\nPhase %i endpoint cost function value: \t\t%e",i+1, solution.endpoint_cost[i]);
            	fprintf(outfile,"\nPhase %i integrated part of the cost: \t\t%e", i+1, solution.integrated_cost[i]);
            	fprintf(outfile,"\nPhase %i initial time:\t\t\t\t%e",i+1, (solution.nodes[i])(1));
                fprintf(outfile,"\nPhase %i final time:\t\t\t\t%e",i+1, (solution.nodes[i])("end"));
		fprintf(outfile,"\nPhase %i maximum relative local error\t\t%e", i+1, Max(solution.relative_errors[i]) );

	    }
        }
    }

    if ( algorithm.nlp_method == "SNOPT") {
        if (solution.nlp_return_code  == 0) {
            fprintf(outfile,"\nOptimal (unscaled) cost function value: \t%e", solution.cost);
            for (i=0;i < problem.nphases; i++) {
		mv = mean(tra(solution.relative_errors[i]));
            	fprintf(outfile,"\nPhase %i endpoint cost function value:\t\t%e",i+1, solution.endpoint_cost[i]);
            	fprintf(outfile,"\nPhase %i integrated part of the cost: \t\t%e", i+1, solution.integrated_cost[i]);
            	fprintf(outfile,"\nPhase %i initial time:\t\t\t\t%e",i+1, (solution.nodes[i])(1));
                fprintf(outfile,"\nPhase %i final time:\t\t\t\t%e",i+1, (solution.nodes[i])("end"));
		fprintf(outfile,"\nPhase %i maximum relative local error\t\t%e", i+1, Max(solution.relative_errors[i]) );

	    }
            auxstr = "Finished successfully";
        }
        else {
           auxstr = "*** The problem FAILED! - see screen output";
           fprintf(outfile,"\nReturned (unscaled) cost function value: \t%e", solution.cost);
            for (i=0;i < problem.nphases; i++) {
		mv = mean(tra(solution.relative_errors[i]));
            	fprintf(outfile,"\nPhase %i endpoint cost function value: \t\t%e",i+1, solution.endpoint_cost[i]);
            	fprintf(outfile,"\nPhase %i integrated part of the cost: \t\t%e", i+1, solution.integrated_cost[i]);
            	fprintf(outfile,"\nPhase %i initial time:\t\t\t\t%e",i+1, (solution.nodes[i])(1));
                fprintf(outfile,"\nPhase %i final time:\t\t\t\t%e",i+1, (solution.nodes[i])("end"));
		fprintf(outfile,"\nPhase %i maximum relative local error\t\t%e", i+1, Max(solution.relative_errors[i]) );

	    }
        }
    }

    fprintf(outfile,"\nNLP solver reports: \t\t\t\t%s\n", auxstr.c_str() );

    fclose(outfile);


#ifndef WIN32
    auxstr = "cat " + mesh_stats_file;
#else
	auxstr = "type " + mesh_stats_file;
#endif

		int ret = system(auxstr.c_str());
		(void) ret;


#ifndef WIN32
    auxstr = "cat " + filename;
#else
	auxstr = "type " + filename;
#endif

		ret = system(auxstr.c_str());
		(void) ret;



}





void print_algorithm_summary(Prob& problem, Alg& algorithm, Sol& solution, Workspace* workspace)
{
    FILE * outfile = workspace->psopt_solution_summary_file;
    string amrtype;

    fprintf(outfile,"\n*********************************************************************************************************");
    fprintf(outfile,"\n***************************************** PSOPT RUN SUMMARY *********************************************");
    fprintf(outfile,"\n*********************************************************************************************************");
    fprintf(outfile,"\n\n PROBLEM NAME:                   %s\n", problem.name.c_str() );
    fprintf(outfile,"\n PSOPT RELEASE NUMBER:           %s\n", PSOPT_RELEASE_STRING );
    fprintf(outfile,"\n DATE AND TIME OF RUN START:     %s", solution.start_date_and_time.c_str() );
    fprintf(outfile,"\n DATE AND TIME OF RUN END:       %s", solution.end_date_and_time.c_str()   );


    fprintf(outfile,"\n*********************************************************************************************************");
    fprintf(outfile,"\n***************************************** ALGORITHM OPTIONS *********************************************");
    fprintf(outfile,"\n*********************************************************************************************************");
    fprintf(outfile,"\nCOLLOCATION METHOD:             %s", algorithm.collocation_method.c_str()   );
    if (use_global_collocation(algorithm)) {
    fprintf(outfile,"\nDIFFERENTIATION MATRIX:         %s", algorithm.diff_matrix.c_str()   );
    }
    fprintf(outfile,"\nNLP METHOD:                     %s", algorithm.nlp_method.c_str()   );
    if (algorithm.nlp_method == "IPOPT") {
    fprintf(outfile,"\nHESSIAN OPTION:                 %s", algorithm.hessian.c_str()   );
    }
    fprintf(outfile,"\nNLP TOLERANCE:                  %e", algorithm.nlp_tolerance   );
    fprintf(outfile,"\nNLP MAX ITERATIONS:             %i", algorithm.nlp_iter_max   );
    fprintf(outfile,"\nSCALING METHOD:                 %s", algorithm.scaling.c_str()   );
    fprintf(outfile,"\nDEFECT SCALING:                 %s", algorithm.defect_scaling.c_str()   );
    fprintf(outfile,"\nDIFFERENTIATION:                %s", algorithm.derivatives.c_str()   );

    if (algorithm.mesh_refinement == "manual") {
        amrtype = "";
    }
    else if (use_global_collocation(algorithm) ) {
        amrtype = " (global variant)";
    }
    else {
        amrtype = " (local variant)";
    }

    amrtype = algorithm.mesh_refinement + amrtype;

    fprintf(outfile,"\nMESH REFINEMENT:                %s", amrtype.c_str()  );
    if (algorithm.mesh_refinement == "automatic" )  {
    fprintf(outfile,"\nMESH REF. ODE TOLERANCE:        %e", algorithm.ode_tolerance   );
    fprintf(outfile,"\nMESH REF. MAX ITERATIONS:       %i", algorithm.mr_max_iterations   );
    fprintf(outfile,"\nMESH REF. MAX INCREMENT FACTOR: %e", algorithm.mr_max_increment_factor   );
      if (use_global_collocation(algorithm)) {
    fprintf(outfile,"\nMESH REF. INITIAL INCREMENT:    %i", algorithm.mr_initial_increment   );
    fprintf(outfile,"\nMESH REF. MIN EXTRAPOL. POINTS: %i", algorithm.mr_min_extrapolation_points   );
      }
      else {
    fprintf(outfile,"\nMESH REF. KAPPA:                %e", algorithm.mr_kappa   );
    fprintf(outfile,"\nMESH REF. M1:                   %i", algorithm.mr_M1   );
    fprintf(outfile,"\nMESH REF. SWITCH ORDER AT ITER: %i", algorithm.switch_order   );
      }

    }




}

void print_solution_summary(Prob& problem, Alg& algorithm, Sol& solution, Workspace* workspace)
{
    FILE * outfile = workspace->psopt_solution_summary_file;

    int i,j,k;

    string auxstr;
    DMatrix mv(1);

    fprintf(outfile,"\n*********************************************************************************************************");
    fprintf(outfile,"\n*****************************************  SOLUTION SUMMARY *********************************************");
    fprintf(outfile,"\n*********************************************************************************************************\n");


    DMatrix Cp, plow, phigh, p, r;


    fprintf(outfile,"\nTotal CPU time (seconds):\t\t\t%e", solution.cpu_time);

    if ( algorithm.nlp_method == "IPOPT") {
        if (solution.nlp_return_code  == 0) {
            fprintf(outfile,"\nOptimal (unscaled) cost function value: \t%e", solution.cost);
            for (i=0;i < problem.nphases; i++) {
            	fprintf(outfile,"\nPhase %i endpoint cost function value:\t\t%e",i+1, solution.endpoint_cost[i]);
            	fprintf(outfile,"\nPhase %i integrated part of the cost: \t\t%e", i+1, solution.integrated_cost[i]);
            	fprintf(outfile,"\nPhase %i initial time:\t\t\t\t%e",i+1, (solution.nodes[i])(1));
                fprintf(outfile,"\nPhase %i final time:\t\t\t\t%e",i+1, (solution.nodes[i])("end"));
		fprintf(outfile,"\nPhase %i maximum relative local error:\t\t%e", i+1, Max(solution.relative_errors[i]) );

	    }
            auxstr = "The problem solved!";
        }
        else {
           auxstr = "*** The problem FAILED! - see screen output";
           fprintf(outfile,"\nReturned (unscaled) cost function value: \t%e", solution.cost);
            for (i=0;i < problem.nphases; i++) {
            	fprintf(outfile,"\nPhase %i endpoint cost function value: \t\t%e",i+1, solution.endpoint_cost[i]);
            	fprintf(outfile,"\nPhase %i integrated part of the cost: \t\t%e", i+1, solution.integrated_cost[i]);
            	fprintf(outfile,"\nPhase %i initial time:\t\t\t\t%e",i+1, (solution.nodes[i])(1));
                fprintf(outfile,"\nPhase %i final time:\t\t\t\t%e",i+1, (solution.nodes[i])("end"));
		fprintf(outfile,"\nPhase %i maximum relative local error\t\t%e", i+1, Max(solution.relative_errors[i]) );

	    }
        }
    }

    if ( algorithm.nlp_method == "SNOPT") {
        if (solution.nlp_return_code  == 0) {
            fprintf(outfile,"\nOptimal (unscaled) cost function value: \t%e", solution.cost);
            for (i=0;i < problem.nphases; i++) {
            	fprintf(outfile,"\nPhase %i endpoint cost function value:\t\t%e",i+1, solution.endpoint_cost[i]);
            	fprintf(outfile,"\nPhase %i integrated part of the cost: \t\t%e", i+1, solution.integrated_cost[i]);
            	fprintf(outfile,"\nPhase %i initial time:\t\t\t\t%e",i+1, (solution.nodes[i])(1));
                fprintf(outfile,"\nPhase %i final time:\t\t\t\t%e",i+1, (solution.nodes[i])("end"));
		fprintf(outfile,"\nPhase %i maximum relative local error\t\t%e", i+1, Max(solution.relative_errors[i]) );

	    }
            auxstr = "Finished successfully";
        }
        else {
           auxstr = "*** The problem FAILED! - see screen output";
           fprintf(outfile,"\nReturned (unscaled) cost function value: \t%e", solution.cost);
            for (i=0;i < problem.nphases; i++) {
            	fprintf(outfile,"\nPhase %i endpoint cost function value: \t\t%e",i+1, solution.endpoint_cost[i]);
            	fprintf(outfile,"\nPhase %i integrated part of the cost: \t\t%e", i+1, solution.integrated_cost[i]);
            	fprintf(outfile,"\nPhase %i initial time:\t\t\t\t%e",i+1, (solution.nodes[i])(1));
                fprintf(outfile,"\nPhase %i final time:\t\t\t\t%e",i+1, (solution.nodes[i])("end"));
		fprintf(outfile,"\nPhase %i maximum relative local error\t\t%e", i+1, Max(solution.relative_errors[i]) );

	    }
        }
    }

    fprintf(outfile,"\nNLP solver reports: \t\t\t\t%s", auxstr.c_str() );
    fprintf(outfile,"\nNLP return code: \t\t\t\t%i", solution.nlp_return_code );
    fprintf(outfile,"\nInternal scaling for objective function \t%e", problem.scale.objective );


    for(i=1;i<=problem.nphases;i++) {


    fprintf(outfile,"\n*****************************************  PHASE %i GRID POINTS (TIME) ***********************************", i);

      for (k=1; k<= problem.phases(i).current_number_of_intervals+1;k++) {

	    fprintf(outfile,"\n%e", solution.nodes[i-1](k));


      }


    if (problem.phases(i).ncontrols>0) {


    fprintf(outfile,"\n*****************************************  PHASE %i CONTROLS *******************************************", i);

      for (k=1; k<= problem.phases(i).current_number_of_intervals+1;k++) {
	  fprintf(outfile,"\n");
	  for(j=1;j<=problem.phases(i).ncontrols;j++) {
	    fprintf(outfile,"%e\t", solution.controls[i-1](j,k));
	  }

      }

    }


    if (problem.phases(i).nstates>0) {

    fprintf(outfile,"\n*****************************************  PHASE %i STATES *******************************************", i);

      for (k=1; k<= problem.phases(i).current_number_of_intervals+1;k++) {
	  fprintf(outfile,"\n");
	  for(j=1;j<=problem.phases(i).nstates;j++) {
	    fprintf(outfile,"%e\t", solution.states[i-1](j,k));
	  }

      }
    }

    if (problem.phases(i).nparameters>0) {
    fprintf(outfile,"\n*****************************************  PHASE %i PARAMETERS *******************************************", i);


    fprintf(outfile,"\n");
    for(j=1;j<=problem.phases(i).nparameters;j++) {
	    fprintf(outfile,"\n%e", solution.parameters[i-1](j));
    }


    }


    }

    if ( problem.observation_function!=NULL && algorithm.parameter_statistics == "yes") {

    fprintf(outfile,"\n****************************************** PARAMETER STATISTICS *****************************************");

    bool peout = compute_parameter_statistics(Cp, p, plow, phigh,r, workspace);

    int pcount = 0;

    if (peout) {



      fprintf(outfile,"\n>>>>> Parameter covariance matrix (all phases) ");

      for(i=1; i<=Cp.GetNoRows();i++) {
        fprintf(outfile,"\n");
        for(j=1; j<=Cp.GetNoCols();j++) {
             fprintf(outfile,"%e\t\t",Cp(i,j));
        }
      }

#ifdef UNIX_IGNORED
// _IGNORED added due to ambiguous call to the rank() function
// GCC 6.3 could not match the correct call:
// dmatrixv.h: int rank(const DMatrix &)
// dmatrixv.h: int rank(const SparseMatrix &)
// /usr/include/c++/6/type_traits: template<class> struct std::rank
//
// TODO: eliminating the using std statement my solve the problem.
//
     fprintf(outfile,"\n\n>>>>> Rank of parameter covariance matrix: %i ", rank(Cp);
#endif
      fprintf(outfile,"\n\n>>> 95 percent statistical confidence limits on estimated parameters ");
      fprintf(outfile,"\nPhase\tParameter\t(Low Confidence Limit) \t(Value) \t\t(High Confidence Limit)");


      for (int iphase=1; iphase<=problem.nphases; iphase++)
      {


          for(i=0;i< problem.phases(iphase).nparameters;i++) {

            j= pcount+i+1;

            fprintf(outfile,"\n%i\t%i\t\t%e\t\t%e\t\t%e", iphase, i+1, plow(j), p(j), phigh(j));

          }

          pcount += problem.phases(iphase).nparameters;


      }

    }

    else {

       fprintf(outfile,"\n *** Unable to compute confidence limits for estimated parameters");

    }

      pcount = 0;

      fprintf(outfile,"\n\n>>> Residual of observed variables");

      fprintf(outfile,"\nPhase\tTime\t\t (Residuals, each column corresponds to an observed variable)");

      for (int iphase=1; iphase<=problem.nphases; iphase++)
      {

          for(i=0;i< problem.phases(iphase).nsamples;i++) {

                  fprintf(outfile,"\n%i\t%e", iphase, problem.phases(iphase).observation_nodes(i+1) );

              for(j=0;j< problem.phases(iphase).nobserved; j++ ) {

                  k= pcount+i*problem.phases(iphase).nobserved+j+1;

                  fprintf(outfile,"\t%e", r(k));

              }


          }

          pcount += problem.phases(iphase).nsamples*problem.phases(iphase).nobserved;


      }


    }


}


void print_constraint_summary(Prob& problem, Sol& solution, Workspace* workspace)
{

    int i, j, k, l;

    FILE* outfile = workspace->psopt_solution_summary_file;


    DMatrix& X = *workspace->Xip;

    DMatrix& G  = *workspace->Gip;

    DMatrix& xlb    = *workspace->xlb;

    DMatrix& xub    = *workspace->xub;

    DMatrix& cs = *workspace->constraint_scaling;

    int nvars = get_number_nlp_vars(problem, workspace);

    int ncons = get_number_nlp_constraints(problem, workspace);

    double* g_l = new double[ncons];
    double* g_u = new double[ncons];

    double tol    = (workspace->algorithm)->nlp_tolerance;


    for(i=1;i<=nvars;i++) {
       X(i) = solution.xad[i-1].value();
    }

    gg_num(X, &G, workspace);

    get_constraint_bounds(g_l, g_u, workspace);

    int phase_offset  = 0;

       fprintf(outfile,"\n*********************************************************************************************************");
       fprintf(outfile,"\n*************************************** NLP CONSTRAINT SUMMARY ******************************************");
       fprintf(outfile,"\n*********************************************************************************************************\n");


    for(i=0;i< problem.nphases; i++)
    {
	int norder    = problem.phase[i].current_number_of_intervals;
	int nstates   = problem.phase[i].nstates;
	int nevents   = problem.phase[i].nevents;
	int npath     = problem.phase[i].npath;
	int offset;
        int path_offset = phase_offset+nstates*(norder+1)+nevents;
	int ncons_phase_i = get_ncons_phase_i(problem,i, workspace);

       fprintf(outfile,"\n******************************* PHASE %i SCALED DIFFERENTIAL DEFECT CONSTRAINTS **************************", i+1);
       fprintf(outfile,"\nLOWER\t\tG(X)\t\tUPPER\t\tSCALING\t\tDESCRIPTION");

       for(k=1; k<=norder+1; k++)
       {
                for (j=0; j<problem.phase[i].nstates; j++) {
	   	     l = phase_offset+(k-1)*nstates+j;
		     fprintf(outfile,"\n%e\t%e\t%e\t%e\tDEFECT FOR STATE DERIV. %i NODE %i", g_l[l], G(l+1), g_u[l], cs(l+1), j+1, k);
		     if ( g_l[l]-tol>G(l+1) || G(l+1)>g_u[l]+tol ) fprintf(outfile," **BOUND VIOLATED");
       		     if ( (g_l[l]-tol<G(l+1) && G(l+1)<g_l[l]+tol) || (g_u[l]-tol<G(l+1) && G(l+1)<g_u[l]+tol) ) fprintf(outfile," **AT BOUND");

		}
       }
       fprintf(outfile,"\n************************************* PHASE %i SCALED PATH CONSTRAINTS ************************************", i+1);
       fprintf(outfile,"\nLOWER\t\tG(X)\t\tUPPER\t\tSCALING\t\tDESCRIPTION");
       for(k=1; k<=norder+1; k++)
       {
	        for (j=0; j<npath; j++)
	        {
		     l = path_offset + (k-1)*npath + j;
		     fprintf(outfile,"\n%e\t%e\t%e\t%e\tPATH CONSTRAINT %i NODE %i", g_l[l], G(l+1), g_u[l], cs(l+1),j+1,k);
		     if ( g_l[l]-tol>G(l+1) || G(l+1)>g_u[l]+tol ) fprintf(outfile," **BOUND VIOLATED");
     		     if ( (g_l[l]-tol<G(l+1) && G(l+1)<g_l[l]+tol) || (g_u[l]-tol<G(l+1) && G(l+1)<g_u[l]+tol) ) fprintf(outfile," **AT BOUND");

                }
       }
       offset = phase_offset+nstates*(norder+1);
       fprintf(outfile,"\n************************************ PHASE %i SCALED EVENT CONSTRAINTS  ***********************************",i+1);
       fprintf(outfile,"\nLOWER\t\tG(X)\t\tUPPER\t\tSCALING\t\tDESCRIPTION");

	for (k=0; k<nevents;k++) {
		j = offset + k;
		fprintf(outfile,"\n%e\t%e\t%e\t%e\tEVENT CONSTRAINT %i", g_l[j], G(j+1), g_u[j], cs(j+1),k+1);
	        if ( g_l[j]-tol>G(j+1) || G(j+1)>g_u[j]+tol ) fprintf(outfile," **BOUND VIOLATED");
		if ( (g_l[j]-tol<G(j+1) && G(j+1)<g_l[j]+tol) || (g_u[j]-tol<G(j+1) && G(j+1)<g_u[j]+tol)) fprintf(outfile," **AT BOUND");

  	}
	// Add tf >= t0 constraint [ t0MIN-tfMAX <= t0-tf <= 0 ]

       fprintf(outfile,"\n*********************************** PHASE %i SCALED tf >= t0 CONSTRAINT ***********************************",i+1);
       fprintf(outfile,"\nLOWER\t\tG(X)\t\tUPPER\t\tSCALING");
       j = phase_offset + ncons_phase_i - 1;
       fprintf(outfile,"\n%e\t%e\t%e\t%e", g_l[j], G(j+1), g_u[j], cs(j+1));

       if ( g_l[j]-tol>G(j+1) || G(j+1)>g_u[j]+tol ) fprintf(outfile," **BOUND VIOLATED");
       if ( (g_l[j]-tol<G(j+1) && G(j+1)<g_l[j]+tol) || (g_u[j]-tol<G(j+1) && G(j+1)<g_u[j]+tol)) fprintf(outfile," **AT BOUND");

       phase_offset += ncons_phase_i;
    }

       fprintf(outfile,"\n************************************* SCALED PHASE LINKAGE CONSTRAINTS ***********************************");
       fprintf(outfile,"\nLOWER\t\tG(X)\t\tUPPER\t\tSCALING\t\tDESCRIPTION");

    for(j=0;j<problem.nlinkages;j++)
    {
     	int l = phase_offset+j;
	fprintf(outfile,"\n%e\t%e\t%e\t%e\tLINKAGE CONSTRAINT %i", g_l[l], G(l+1), g_u[l], cs(l+1),j+1);
	if ( g_l[l]-tol>G(l+1) || G(l+1)>g_u[l]+tol ) fprintf(outfile," **BOUND VIOLATED");
        if ( (g_l[l]-tol<G(l+1) && G(l+1)<g_l[l]+tol) || (g_u[l]-tol<G(l+1) && G(l+1)<g_u[l]+tol) ) fprintf(outfile," **AT BOUND");

    }


    DMatrix& control_scaling = problem.phase[i].scale.controls;
    DMatrix& state_scaling   = problem.phase[i].scale.states;
    DMatrix& param_scaling   = problem.phase[i].scale.parameters;
    double time_scaling      =  problem.phase[i].scale.time;

      fprintf(outfile,"\n**************************************UNSCALED NLP DECISION VARIABLES *************************************");
      fprintf(outfile,"\nJ\tLOWER\t\tX(J)\t\tUPPER\t\tSCALING\t\tDESCRIPTION");


    int ii;

    for(i=0;i< problem.nphases; i++)
    {

        DMatrix& control_scaling = problem.phase[i].scale.controls;
	DMatrix& state_scaling   = problem.phase[i].scale.states;
	DMatrix& param_scaling   = problem.phase[i].scale.parameters;
	double time_scaling      =  problem.phase[i].scale.time;
	int norder    = problem.phase[i].current_number_of_intervals;
	int nstates   = problem.phase[i].nstates;
        int ncontrols = problem.phase[i].ncontrols;
        int nparam    = problem.phase[i].nparameters;
	int offset;
        int iphase_offset = get_iphase_offset(problem,i+1, workspace);
	int nvars_phase_i = get_nvars_phase_i(problem,i, workspace);
        int offset1 = (norder+1)*ncontrols;
        int offset2 = (norder+1)*(ncontrols+nstates);


	for (k=1; k<=norder+1; k++) {

                for (ii=1;ii<=ncontrols;ii++) {
                        j = iphase_offset+(k-1)*ncontrols+ii;
			fprintf(outfile,"\n%i\t%e\t%e\t%e\t%e\tCONTROL %i NODE %i PHASE %i", j, xlb(j)/control_scaling(ii),
				  X(j)/control_scaling(ii), xub(j)/control_scaling(ii),  control_scaling(ii), ii, k, i+1);
			if ( xlb(j)-tol>X(j) || X(j)>xub(j)+tol ) fprintf(outfile," **BOUND VIOLATED");
   		        if ( (xlb(j)-tol<X(j) && X(j)<xlb(j)+tol) || (xub(j)-tol<X(j) && X(j)<xub(j)+tol) ) fprintf(outfile," **AT BOUND");

		}

	}

	for (k=1; k<=norder+1; k++) {


                for (ii=1;ii<=nstates;ii++) {
                        j = iphase_offset+(k-1)*nstates+offset1+ii;
			fprintf(outfile,"\n%i\t%e\t%e\t%e\t%e\tSTATE %i NODE %i PHASE %i", j, xlb(j)/state_scaling(ii),
				X(j)/state_scaling(ii), xub(j)/state_scaling(ii), state_scaling(ii), ii, k, i+1);
			if ( xlb(j)-tol>X(j) || X(j)>xub(j)+tol ) fprintf(outfile," **BOUND VIOLATED");
   		        if ( (xlb(j)-tol<X(j) && X(j)<xlb(j)+tol) || (xub(j)-tol<X(j) && X(j)<xub(j)+tol) ) fprintf(outfile," **AT BOUND");

		}


	}

        for (ii=1;ii<=nparam;ii++) {
                        j = iphase_offset+offset2+ii;
			fprintf(outfile,"\n%i\t%e\t%e\t%e\t%e\tPARAMETER %i PHASE %i", j, xlb(j)/param_scaling(ii),
				X(j)/param_scaling(ii), xub(j)/param_scaling(ii), param_scaling(ii), ii, i+1);
			if ( xlb(j)-tol>X(j) || X(j)>xub(j)+tol ) fprintf(outfile," **BOUND VIOLATED");
   		        if ( (xlb(j)-tol<X(j) && X(j)<xlb(j)+tol) || (xub(j)-tol<X(j) && X(j)<xub(j)+tol) ) fprintf(outfile," **AT BOUND");

	}

        if (need_midpoint_controls(*workspace->algorithm, workspace)) {

		for (k=1; k<=norder+1; k++) {

			for (ii=1;ii<=ncontrols;ii++) {
				j = iphase_offset+offset2+nparam+(k-1)*ncontrols+ii;
				fprintf(outfile,"\n%i\t%e\t%e\t%e\t%e\tMIDPOINT CONTROL %i NODE %i PHASE %i", j,
					 xlb(j)/control_scaling(ii), X(j)/control_scaling(ii), xub(j)/control_scaling(ii),
					control_scaling(ii), ii, k, i+1);
				if ( xlb(j)-tol>X(j) || X(j)>xub(j)+tol ) fprintf(outfile," **BOUND VIOLATED");
   		                if ( (xlb(j)-tol<X(j) && X(j)<xlb(j)+tol) || (xub(j)-tol<X(j) && X(j)<xub(j)+tol) ) fprintf(outfile," **AT BOUND");

			}

		}
	}

        j = iphase_offset + nvars_phase_i-1;

	fprintf(outfile,"\n%i\t%e\t%e\t%e\t%e\tt0 PHASE %i", j, xlb(j)/time_scaling, X(j)/time_scaling,
		                                                xub(j)/time_scaling, time_scaling, i+1);
	if ( xlb(j)-tol>X(j) || X(j)>xub(j)+tol ) fprintf(outfile," **BOUND VIOLATED");
        if ( (xlb(j)-tol<X(j) && X(j)<xlb(j)+tol) || (xub(j)-tol<X(j) && X(j)<xub(j)+tol) ) fprintf(outfile," **AT BOUND");


        j = iphase_offset + nvars_phase_i;

	fprintf(outfile,"\n%i\t%e\t%e\t%e\t%e\ttf PHASE %i", j, xlb(j)/time_scaling, X(j)/time_scaling,
		                                                xub(j)/time_scaling, time_scaling, i+1);
	if ( xlb(j)-tol>X(j) || X(j)>xub(j)+tol ) fprintf(outfile," **BOUND VIOLATED");
        if ( (xlb(j)-tol<X(j) && X(j)<xlb(j)+tol) || (xub(j)-tol<X(j) && X(j)<xub(j)+tol) ) fprintf(outfile," **AT BOUND");



    }

}



